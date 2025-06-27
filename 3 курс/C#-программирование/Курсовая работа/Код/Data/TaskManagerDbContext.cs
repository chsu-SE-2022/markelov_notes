using Microsoft.EntityFrameworkCore;
using TaskManager.Models;

namespace TaskManager.Data
{
    // Класс для работы с базой данных
    public class TaskManagerDbContext : DbContext
    {
        // Таблица с задачами
        public DbSet<KanbanTask> Tasks { get; set; }

        public TaskManagerDbContext(DbContextOptions<TaskManagerDbContext> options)
            : base(options)
        {
        }

        // Настройка правил для таблицы задач
        protected override void OnModelCreating(ModelBuilder modelBuilder)
        {
            base.OnModelCreating(modelBuilder);

            modelBuilder.Entity<KanbanTask>(entity =>
            {
                // Название задачи обязательно
                entity.Property(t => t.Title).IsRequired();
                // Описание может быть пустым
                entity.Property(t => t.Description).IsRequired(false);
            });
        }
    }
} 