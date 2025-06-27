using System;
using System.Collections.Generic;
using System.Threading.Tasks;
using TaskManager.Models;
using Microsoft.EntityFrameworkCore;
using System.Linq;
using TaskManager.Data;

namespace TaskManager.Services
{
    // Реализация сервиса для работы с задачами
    public class TaskService : ITaskService
    {
        // Контекст базы данных
        private readonly TaskManagerDbContext _dbContext;

        // Конструктор с инициализацией контекста базы данных
        public TaskService(TaskManagerDbContext dbContext)
        {
            _dbContext = dbContext ?? throw new ArgumentNullException(nameof(dbContext));
        }

        // Получить все задачи с определенным статусом
        public async Task<List<KanbanTask>> GetTasksByStatusAsync(KanbanTaskStatus status)
        {
            return await _dbContext.Tasks.Where(t => t.Status == status).ToListAsync();
        }

        // Добавить новую задачу
        public async Task<KanbanTask> AddTaskAsync(KanbanTask task)
        {
            await _dbContext.Tasks.AddAsync(task);
            await _dbContext.SaveChangesAsync();
            return task;
        }

        // Обновить существующую задачу
        public async Task UpdateTaskAsync(KanbanTask task)
        {
            _dbContext.Tasks.Update(task);
            await _dbContext.SaveChangesAsync();
        }

        // Удалить задачу по её номеру
        public async Task DeleteTaskAsync(int taskId)
        {
            var taskToRemove = await _dbContext.Tasks.FirstOrDefaultAsync(t => t.Id == taskId);
            if (taskToRemove != null)
            {
                _dbContext.Tasks.Remove(taskToRemove);
                await _dbContext.SaveChangesAsync();
            }
        }
    }
} 