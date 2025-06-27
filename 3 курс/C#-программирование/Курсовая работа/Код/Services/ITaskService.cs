using System.Collections.Generic;
using System.Threading.Tasks;
using TaskManager.Models;

namespace TaskManager.Services
{
    // Интерфейс для работы с задачами (добавление, получение, обновление, удаление)
    public interface ITaskService
    {
        // Получить все задачи с определенным статусом
        Task<List<KanbanTask>> GetTasksByStatusAsync(KanbanTaskStatus status);

        // Добавить новую задачу
        Task<KanbanTask> AddTaskAsync(KanbanTask task);

        // Обновить существующую задачу
        Task UpdateTaskAsync(KanbanTask task);

        // Удалить задачу по её номеру
        Task DeleteTaskAsync(int taskId);
    }
} 