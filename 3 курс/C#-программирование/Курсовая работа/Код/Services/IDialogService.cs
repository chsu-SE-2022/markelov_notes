namespace TaskManager.Services
{
    public interface IDialogService
    {
        void ShowError(string message, string title = "Ошибка");
        void ShowWarning(string message, string title = "Предупреждение");
        void ShowInfo(string message, string title = "Информация");
    }
} 