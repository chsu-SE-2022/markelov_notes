namespace TransportClient.Models;

public class RouteDto
{
    public int Id { get; set; }
    public string Name { get; set; } = string.Empty;
    public string Number { get; set; } = string.Empty;
    public string TransportType { get; set; } = "Bus";
    public bool Active { get; set; } = true;
    public DateTime CreatedAt { get; set; }
}
