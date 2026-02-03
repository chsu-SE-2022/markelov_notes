using System.Collections.Generic;

namespace NetworkCalc
{
    public enum SegmentType
    {
        Ethernet10Base5,
        Ethernet10Base2,
        Ethernet10BaseT,
        Ethernet10BaseFL,
        FOIRL,
        AUI
    }

    public sealed class PdvEntry
    {
        public SegmentType Type { get; set; }
        public double MaxLengthMeters { get; set; }
        public double LeftBaseBits { get; set; }
        public double MidBaseBits { get; set; }
        public double RightBaseBits { get; set; }
        public double PerMeterBits { get; set; }
    }

    public sealed class PvvEntry
    {
        public SegmentType Type { get; set; }
        public double RepeaterShrinkBits { get; set; }
    }

    public sealed class Segment
    {
        public SegmentType Type { get; set; }
        public int LengthMeters { get; set; }
    }

    public static class Defaults
    {
        public static List<PdvEntry> Pdv() => new()
        {
            new PdvEntry{ Type=SegmentType.Ethernet10Base5, MaxLengthMeters=500, LeftBaseBits=11.1, MidBaseBits=46.5, RightBaseBits=169.5, PerMeterBits=0.103 },
            new PdvEntry{ Type=SegmentType.Ethernet10Base2, MaxLengthMeters=185, LeftBaseBits=11.8, MidBaseBits=46.5, RightBaseBits=169.5, PerMeterBits=0.107 },
            new PdvEntry{ Type=SegmentType.Ethernet10BaseT, MaxLengthMeters=100, LeftBaseBits=7.3, MidBaseBits=10.53, RightBaseBits=50.5, PerMeterBits=0.11 },
            new PdvEntry{ Type=SegmentType.Ethernet10BaseFL, MaxLengthMeters=2000, LeftBaseBits=7.8, MidBaseBits=29.0, RightBaseBits=152.0, PerMeterBits=0.01 },
            new PdvEntry{ Type=SegmentType.FOIRL, MaxLengthMeters=1000, LeftBaseBits=7.8, MidBaseBits=29.0, RightBaseBits=152.0, PerMeterBits=0.01 },
            new PdvEntry{ Type=SegmentType.AUI, MaxLengthMeters=50, LeftBaseBits=0, MidBaseBits=0, RightBaseBits=0, PerMeterBits=0.103 },
        };

        public static List<PvvEntry> Pvv() => new()
        {
            new PvvEntry{ Type=SegmentType.Ethernet10Base5, RepeaterShrinkBits=9 },
            new PvvEntry{ Type=SegmentType.Ethernet10Base2, RepeaterShrinkBits=9 },
            new PvvEntry{ Type=SegmentType.Ethernet10BaseT, RepeaterShrinkBits=8 },
            new PvvEntry{ Type=SegmentType.Ethernet10BaseFL, RepeaterShrinkBits=5 },
            new PvvEntry{ Type=SegmentType.FOIRL, RepeaterShrinkBits=5 },
            new PvvEntry{ Type=SegmentType.AUI, RepeaterShrinkBits=0 },
        };
    }
}
