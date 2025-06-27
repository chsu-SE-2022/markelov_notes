using System.Windows.Controls;
using System.Windows.Input;
using TaskManager.ViewModels;

namespace TaskManager.Views
{
    public partial class NotificationView : UserControl
    {
        public NotificationView()
        {
            InitializeComponent();
            MouseLeftButtonDown += NotificationView_MouseLeftButtonDown;
        }

        private void NotificationView_MouseLeftButtonDown(object sender, MouseButtonEventArgs e)
        {
            if (DataContext is NotificationViewModel viewModel && viewModel.CloseCommand.CanExecute(null))
            {
                viewModel.CloseCommand.Execute(null);
            }
        }
    }
} 