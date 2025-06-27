using System.Collections.ObjectModel;
using TaskManager.ViewModels;
using System.Linq;

namespace TaskManager.Services
{
    public class NotificationService : INotificationService
    {
        private readonly ObservableCollection<NotificationViewModel> _notifications;

        public NotificationService()
        {
            _notifications = new ObservableCollection<NotificationViewModel>();
        }

        public ObservableCollection<NotificationViewModel> Notifications => _notifications;

        public void ShowNotification(string message)
        {
            // Удаляем старые скрытые уведомления, чтобы коллекция не росла бесконечно
            var hidden = _notifications.Where(n => !n.IsVisible).ToList();
            foreach (var notification in hidden)
            {
                _notifications.Remove(notification);
            }

            var notificationViewModel = new NotificationViewModel(message);
            _notifications.Add(notificationViewModel);
            notificationViewModel.ShowNotification();
        }
    }
} 