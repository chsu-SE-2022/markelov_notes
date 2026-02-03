namespace TransportApi.Models;

public class Route
{
    public int Id { get; set; }
    public string Name { get; set; } = string.Empty;
    public string Number { get; set; } = string.Empty;
    public string TransportType { get; set; } = "Bus"; // Bus/Tram/Metro
    public bool Active { get; set; } = true;
    public DateTime CreatedAt { get; set; } = DateTime.UtcNow;

    public List<Stop> Stops { get; set; } = new();
}
