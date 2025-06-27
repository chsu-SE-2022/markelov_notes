using System;

namespace TaskManager.Models
{
    // Класс для хранения информации о задаче в системе Kanban
    public class KanbanTask : ICloneable
    {
        public int Id { get; set; }
        public string Title { get; set; }
        public string Description { get; set; }
        public KanbanTaskStatus Status { get; set; }
        public DateTime CreatedAt { get; set; }
        public DateTime? DueDate { get; set; }
        public int Priority { get; set; }

        // Создать копию задачи
        public object Clone()
        {
            return new KanbanTask
            {
                Id = this.Id,
                Title = this.Title,
                Description = this.Description,
                Status = this.Status,
                CreatedAt = this.CreatedAt,
                DueDate = this.DueDate,
                Priority = this.Priority
            };
        }
    }
} 