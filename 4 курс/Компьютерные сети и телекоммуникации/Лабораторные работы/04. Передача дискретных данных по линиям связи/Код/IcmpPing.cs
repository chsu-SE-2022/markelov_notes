using System.Net;
using System.Net.NetworkInformation;
using System.Net.Sockets;
using System.Linq;
using System.Runtime.InteropServices;

namespace WinFormsApp1
{
    internal static class IcmpPing
    {
        [DllImport("iphlpapi.dll", SetLastError = true)]
        private static extern IntPtr IcmpCreateFile();

        [DllImport("iphlpapi.dll", SetLastError = true)]
        private static extern bool IcmpCloseHandle(IntPtr handle);

        [DllImport("iphlpapi.dll", SetLastError = true)]
        private static extern uint IcmpSendEcho(
            IntPtr icmpHandle,
            uint destinationAddress,
            IntPtr requestData,
            ushort requestSize,
            ref IpOptionInformation requestOptions,
            IntPtr replyBuffer,
            uint replySize,
            uint timeout);

        [StructLayout(LayoutKind.Sequential)]
        private struct IpOptionInformation
        {
            public byte Ttl;
            public byte Tos;
            public byte Flags;
            public byte OptionsSize;
            public IntPtr OptionsData;
        }

        [StructLayout(LayoutKind.Sequential)]
        private struct IcmpEchoReply
        {
            public uint Address;
            public uint Status;
            public uint RoundTripTime;
            public ushort DataSize;
            public ushort Reserved;
            public IntPtr Data;
            public IpOptionInformation Options;
        }

        internal sealed class Reply
        {
            public required IPAddress Address { get; init; }
            public required IPStatus Status { get; init; }
            public required long RoundtripTime { get; init; }
            public required int DataSize { get; init; }
            public required int Ttl { get; init; }
        }

        public static Reply Send(string hostnameOrAddress, uint timeoutMs, byte[] buffer, byte ttl = 128)
        {
            IPAddress address = ResolveIPv4(hostnameOrAddress);

            IntPtr handle = IcmpCreateFile();
            if (handle == IntPtr.Zero || handle == new IntPtr(-1))
            {
                throw new InvalidOperationException("IcmpCreateFile failed.");
            }

            IntPtr requestData = IntPtr.Zero;
            IntPtr replyBuffer = IntPtr.Zero;

            try
            {
                ushort requestSize = (ushort)(buffer?.Length ?? 0);

                if (buffer != null && requestSize > 0)
                {
                    requestData = Marshal.AllocHGlobal(requestSize);
                    Marshal.Copy(buffer, 0, requestData, requestSize);
                }

                uint replySize = (uint)(Marshal.SizeOf<IcmpEchoReply>() + requestSize + 8);
                replyBuffer = Marshal.AllocHGlobal((int)replySize);

                IpOptionInformation options = new IpOptionInformation
                {
                    Ttl = ttl,
                    Tos = 0,
                    Flags = 0,
                    OptionsSize = 0,
                    OptionsData = IntPtr.Zero
                };

                uint destinationAddress = ToIPv4Uint(address);

                uint numReplies = IcmpSendEcho(
                    handle,
                    destinationAddress,
                    requestData,
                    requestSize,
                    ref options,
                    replyBuffer,
                    replySize,
                    timeoutMs);

                if (numReplies == 0)
                {
                    return new Reply
                    {
                        Address = address,
                        Status = (IPStatus)Marshal.GetLastWin32Error(),
                        RoundtripTime = 0,
                        DataSize = 0,
                        Ttl = 0
                    };
                }

                IcmpEchoReply nativeReply = Marshal.PtrToStructure<IcmpEchoReply>(replyBuffer);
                IPAddress replyAddress = FromIPv4Uint(nativeReply.Address);

                return new Reply
                {
                    Address = replyAddress,
                    Status = (IPStatus)nativeReply.Status,
                    RoundtripTime = nativeReply.RoundTripTime,
                    DataSize = nativeReply.DataSize,
                    Ttl = nativeReply.Options.Ttl
                };
            }
            finally
            {
                if (replyBuffer != IntPtr.Zero)
                {
                    Marshal.FreeHGlobal(replyBuffer);
                }

                if (requestData != IntPtr.Zero)
                {
                    Marshal.FreeHGlobal(requestData);
                }

                IcmpCloseHandle(handle);
            }
        }

        private static IPAddress ResolveIPv4(string hostnameOrAddress)
        {
            if (IPAddress.TryParse(hostnameOrAddress, out IPAddress? parsed) && parsed.AddressFamily == AddressFamily.InterNetwork)
            {
                return parsed;
            }

            IPAddress[] addrs = Dns.GetHostAddresses(hostnameOrAddress);
            IPAddress? ipv4 = addrs.FirstOrDefault(a => a.AddressFamily == AddressFamily.InterNetwork);
            if (ipv4 == null)
            {
                throw new InvalidOperationException("IPv4 address not found for host.");
            }

            return ipv4;
        }

        private static uint ToIPv4Uint(IPAddress address)
        {
            byte[] bytes = address.GetAddressBytes();
            if (bytes.Length != 4)
            {
                throw new ArgumentException("Only IPv4 addresses are supported.", nameof(address));
            }

            return (uint)(bytes[0] | (bytes[1] << 8) | (bytes[2] << 16) | (bytes[3] << 24));
        }

        private static IPAddress FromIPv4Uint(uint addr)
        {
            byte[] bytes = new byte[]
            {
                (byte)(addr & 0xFF),
                (byte)((addr >> 8) & 0xFF),
                (byte)((addr >> 16) & 0xFF),
                (byte)((addr >> 24) & 0xFF)
            };

            return new IPAddress(bytes);
        }
    }
}
