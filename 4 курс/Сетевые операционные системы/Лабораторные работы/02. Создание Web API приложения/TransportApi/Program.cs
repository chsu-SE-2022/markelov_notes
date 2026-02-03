using Microsoft.EntityFrameworkCore;
using TransportApi.Data;
using RouteModel = TransportApi.Models.Route;
using StopModel = TransportApi.Models.Stop;

var builder = WebApplication.CreateBuilder(args);

// Add services
builder.Services.AddEndpointsApiExplorer();
builder.Services.AddSwaggerGen();

// EF Core + SQLite
var connectionString = builder.Configuration.GetConnectionString("DefaultConnection") ?? "Data Source=transport.db";
builder.Services.AddDbContext<AppDbContext>(options => options.UseSqlite(connectionString));

var app = builder.Build();

// Ensure database exists (for demo purposes; migrations optional)
using (var scope = app.Services.CreateScope())
{
    var db = scope.ServiceProvider.GetRequiredService<AppDbContext>();
    db.Database.EnsureCreated();
}

// Configure Swagger UI
app.UseSwagger();
app.UseSwaggerUI();

app.UseHttpsRedirection();

// Routes endpoints
app.MapPost("/routes", async (AppDbContext db, RouteModel route) =>
{
    db.Routes.Add(route);
    await db.SaveChangesAsync();
    return Results.Created($"/routes/{route.Id}", route);
}).WithTags("Routes");

app.MapGet("/routes", async (AppDbContext db) =>
    await db.Routes.AsNoTracking().ToListAsync()).WithTags("Routes");

app.MapGet("/routes/{id:int}", async (AppDbContext db, int id) =>
{
    var entity = await db.Routes.Include(r => r.Stops.OrderBy(s => s.SequenceIndex)).FirstOrDefaultAsync(r => r.Id == id);
    return entity is not null ? Results.Ok(entity) : Results.NotFound();
}).WithTags("Routes");

app.MapPut("/routes/{id:int}", async (AppDbContext db, int id, RouteModel input) =>
{
    var entity = await db.Routes.FindAsync(id);
    if (entity is null) return Results.NotFound();
    entity.Name = input.Name;
    entity.Number = input.Number;
    entity.TransportType = input.TransportType;
    entity.Active = input.Active;
    await db.SaveChangesAsync();
    return Results.NoContent();
}).WithTags("Routes");

app.MapPatch("/routes/{id:int}", async (AppDbContext db, int id, RouteModel input) =>
{
    var entity = await db.Routes.FindAsync(id);
    if (entity is null) return Results.NotFound();
    if (!string.IsNullOrWhiteSpace(input.Name)) entity.Name = input.Name;
    if (!string.IsNullOrWhiteSpace(input.Number)) entity.Number = input.Number;
    if (!string.IsNullOrWhiteSpace(input.TransportType)) entity.TransportType = input.TransportType;
    // Active: keep default bool behavior (assume client sends desired value); if not provided, ignore
    entity.Active = input.Active != default ? input.Active : entity.Active;
    await db.SaveChangesAsync();
    return Results.NoContent();
}).WithTags("Routes");

app.MapDelete("/routes/{id:int}", async (AppDbContext db, int id) =>
{
    var entity = await db.Routes.FindAsync(id);
    if (entity is null) return Results.NotFound();
    db.Routes.Remove(entity);
    await db.SaveChangesAsync();
    return Results.NoContent();
}).WithTags("Routes");

// Stops endpoints
app.MapPost("/stops", async (AppDbContext db, StopModel stop) =>
{
    // optional: check route exists
    var routeExists = await db.Routes.AnyAsync(r => r.Id == stop.RouteId);
    if (!routeExists) return Results.BadRequest($"Route {stop.RouteId} not found");
    db.Stops.Add(stop);
    try
    {
        await db.SaveChangesAsync();
    }
    catch (DbUpdateException)
    {
        return Results.Conflict("Stop with the same RouteId and SequenceIndex already exists.");
    }
    return Results.Created($"/stops/{stop.Id}", stop);
}).WithTags("Stops");

app.MapGet("/stops", async (AppDbContext db) =>
    await db.Stops.AsNoTracking().ToListAsync()).WithTags("Stops");

app.MapGet("/stops/{id:int}", async (AppDbContext db, int id) =>
{
    var entity = await db.Stops.AsNoTracking().FirstOrDefaultAsync(s => s.Id == id);
    return entity is not null ? Results.Ok(entity) : Results.NotFound();
}).WithTags("Stops");

app.MapGet("/routes/{routeId:int}/stops", async (AppDbContext db, int routeId) =>
{
    var routeExists = await db.Routes.AnyAsync(r => r.Id == routeId);
    if (!routeExists) return Results.NotFound();
    var stops = await db.Stops.Where(s => s.RouteId == routeId)
                              .OrderBy(s => s.SequenceIndex)
                              .AsNoTracking()
                              .ToListAsync();
    return Results.Ok(stops);
}).WithTags("Stops");

app.MapPut("/stops/{id:int}", async (AppDbContext db, int id, StopModel input) =>
{
    var entity = await db.Stops.FindAsync(id);
    if (entity is null) return Results.NotFound();
    if (input.RouteId != 0)
    {
        var routeExists = await db.Routes.AnyAsync(r => r.Id == input.RouteId);
        if (!routeExists) return Results.BadRequest($"Route {input.RouteId} not found");
        entity.RouteId = input.RouteId;
    }
    entity.Name = input.Name;
    entity.SequenceIndex = input.SequenceIndex;
    entity.Latitude = input.Latitude;
    entity.Longitude = input.Longitude;
    try
    {
        await db.SaveChangesAsync();
    }
    catch (DbUpdateException)
    {
        return Results.Conflict();
    }
    return Results.NoContent();
}).WithTags("Stops");

app.MapPatch("/stops/{id:int}", async (AppDbContext db, int id, StopModel input) =>
{
    var entity = await db.Stops.FindAsync(id);
    if (entity is null) return Results.NotFound();
    if (input.RouteId != 0 && input.RouteId != entity.RouteId)
    {
        var routeExists = await db.Routes.AnyAsync(r => r.Id == input.RouteId);
        if (!routeExists) return Results.BadRequest($"Route {input.RouteId} not found");
        entity.RouteId = input.RouteId;
    }
    if (!string.IsNullOrWhiteSpace(input.Name)) entity.Name = input.Name;
    if (input.SequenceIndex != default) entity.SequenceIndex = input.SequenceIndex;
    if (input.Latitude is not null) entity.Latitude = input.Latitude;
    if (input.Longitude is not null) entity.Longitude = input.Longitude;
    try
    {
        await db.SaveChangesAsync();
    }
    catch (DbUpdateException)
    {
        return Results.Conflict();
    }
    return Results.NoContent();
}).WithTags("Stops");

app.MapDelete("/stops/{id:int}", async (AppDbContext db, int id) =>
{
    var entity = await db.Stops.FindAsync(id);
    if (entity is null) return Results.NotFound();
    db.Stops.Remove(entity);
    await db.SaveChangesAsync();
    return Results.NoContent();
}).WithTags("Stops");

app.Run();

