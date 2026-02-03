using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace DataDevice
{
    public class WiFi : DataDevice
    {
        public double Speed { get; }
        public double Frequency { get; }
        public bool Wireless { get; }
        public WiFi(int id, string name, double speed, double frequency, bool wireless) : base(id, name)
        {
            this.Speed = speed;
            this.Frequency = frequency;
            this.Wireless = wireless;
        }
        protected override string GetDeviceType()
        {
            return "WiFi";
        }
        protected override string GetCharacteristics()
        {
            return $"Скорость: {Speed}\nЧастота: {Frequency}\nПроводной: {Wireless}";
        }
    }
}
