namespace TransportClient.Models;

public class StopDto
{
    public int Id { get; set; }
    public int RouteId { get; set; }
    public string Name { get; set; } = string.Empty;
    public int SequenceIndex { get; set; }
    public double? Latitude { get; set; }
    public double? Longitude { get; set; }
}
