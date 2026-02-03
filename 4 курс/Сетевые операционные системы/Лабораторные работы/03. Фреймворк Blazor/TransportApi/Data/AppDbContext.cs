using Microsoft.EntityFrameworkCore;

namespace TransportApi.Data;

public class AppDbContext(DbContextOptions<AppDbContext> options) : DbContext(options)
{
    public DbSet<TransportApi.Models.Route> Routes => Set<TransportApi.Models.Route>();
    public DbSet<TransportApi.Models.Stop> Stops => Set<TransportApi.Models.Stop>();

    protected override void OnModelCreating(ModelBuilder modelBuilder)
    {
        modelBuilder.Entity<TransportApi.Models.Route>(e =>
        {
            e.Property(x => x.Name).HasMaxLength(200).IsRequired();
            e.Property(x => x.Number).HasMaxLength(50);
            e.Property(x => x.TransportType).HasMaxLength(50).HasDefaultValue("Bus");
            e.HasMany(x => x.Stops)
             .WithOne(x => x.Route!)
             .HasForeignKey(x => x.RouteId)
             .OnDelete(DeleteBehavior.Cascade);
        });

        modelBuilder.Entity<TransportApi.Models.Stop>(e =>
        {
            e.Property(x => x.Name).HasMaxLength(200).IsRequired();
            e.HasIndex(x => new { x.RouteId, x.SequenceIndex }).IsUnique();
        });
    }
}
