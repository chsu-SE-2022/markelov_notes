using System.Net.Http;
using System.Net.Http.Json;
using TransportClient.Models;

namespace TransportClient.Services;

public class ApiClient(HttpClient http)
{
    private readonly HttpClient _http = http;

    // Routes
    public async Task<RouteDto[]?> GetRoutesAsync(CancellationToken ct = default)
        => await _http.GetFromJsonAsync<RouteDto[]>($"/routes?ts={DateTime.UtcNow.Ticks}", ct);

    public async Task<RouteDto?> GetRouteAsync(int id, CancellationToken ct = default)
        => await _http.GetFromJsonAsync<RouteDto>($"/routes/{id}", ct);

    public async Task<RouteDto?> CreateRouteAsync(RouteDto dto, CancellationToken ct = default)
    {
        var resp = await _http.PostAsJsonAsync("/routes", dto, ct);
        if (!resp.IsSuccessStatusCode) return null;
        return await resp.Content.ReadFromJsonAsync<RouteDto>(cancellationToken: ct);
    }

    public async Task<bool> UpdateRouteAsync(int id, RouteDto dto, CancellationToken ct = default)
    {
        var resp = await _http.PutAsJsonAsync($"/routes/{id}", dto, ct);
        return resp.IsSuccessStatusCode;
    }

    public async Task<bool> DeleteRouteAsync(int id, CancellationToken ct = default)
        => (await _http.DeleteAsync($"/routes/{id}", ct)).IsSuccessStatusCode;

    // Stops
    public async Task<StopDto[]?> GetStopsByRouteAsync(int routeId, CancellationToken ct = default)
        => await _http.GetFromJsonAsync<StopDto[]>($"/routes/{routeId}/stops", ct);

    public async Task<StopDto?> GetStopAsync(int id, CancellationToken ct = default)
        => await _http.GetFromJsonAsync<StopDto>($"/stops/{id}", ct);

    public async Task<StopDto?> CreateStopAsync(StopDto dto, CancellationToken ct = default)
    {
        var resp = await _http.PostAsJsonAsync("/stops", dto, ct);
        if (!resp.IsSuccessStatusCode) return null;
        return await resp.Content.ReadFromJsonAsync<StopDto>(cancellationToken: ct);
    }

    public async Task<bool> UpdateStopAsync(int id, StopDto dto, CancellationToken ct = default)
        => (await _http.PutAsJsonAsync($"/stops/{id}", dto, ct)).IsSuccessStatusCode;

    public async Task<bool> DeleteStopAsync(int id, CancellationToken ct = default)
        => (await _http.DeleteAsync($"/stops/{id}", ct)).IsSuccessStatusCode;
}
