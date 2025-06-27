using Prism.Mvvm;
using System;
using System.Threading.Tasks;
using System.Windows.Input;
using Prism.Commands;
using System.Windows.Threading;

namespace TaskManager.ViewModels
{
    public class NotificationViewModel : BindableBase
    {
        private string _message;
        public string Message
        {
            get => _message;
            set => SetProperty(ref _message, value);
        }

        private bool _isVisible;
        public bool IsVisible
        {
            get => _isVisible;
            set => SetProperty(ref _isVisible, value);
        }

        private DispatcherTimer _timer;

        public ICommand CloseCommand { get; }

        public NotificationViewModel(string message)
        {
            Message = message;
            IsVisible = false; // Изначально невидимо
            CloseCommand = new DelegateCommand(HideNotification);

            _timer = new DispatcherTimer();
            _timer.Interval = TimeSpan.FromSeconds(3);
            _timer.Tick += (s, e) => HideNotification();
        }

        public void ShowNotification()
        {
            IsVisible = true;
            _timer.Start();
        }

        private void HideNotification()
        {
            _timer.Stop();
            IsVisible = false;
        }
    }
} 