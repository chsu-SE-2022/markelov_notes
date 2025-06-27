namespace TaskManager.Models
{
    // Возможные статусы задачи в системе Kanban
    public enum KanbanTaskStatus
    {
        // Задача в списке ожидания
        Backlog,
        
        // Задача запрошена для выполнения
        Request,
        
        // Задача выбрана для работы
        Selected,
        
        // Задача в процессе выполнения
        InProgress,
        
        // Задача выполнена
        Completed
    }
} 