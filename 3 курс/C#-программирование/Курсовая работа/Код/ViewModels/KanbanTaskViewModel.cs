using Prism.Mvvm;
using TaskManager.Models;

namespace TaskManager.ViewModels
{
    public class KanbanTaskViewModel : BindableBase
    {
        private readonly KanbanTask _task;
        private bool _isEditing;

        public KanbanTaskViewModel(KanbanTask task)
        {
            _task = task;
        }

        public int Id
        {
            get => _task.Id;
            set
            {
                _task.Id = value;
                RaisePropertyChanged();
            }
        }

        public string Title
        {
            get => _task.Title;
            set
            {
                _task.Title = value;
                RaisePropertyChanged();
            }
        }

        public string Description
        {
            get => _task.Description;
            set
            {
                _task.Description = value;
                RaisePropertyChanged();
            }
        }

        public KanbanTaskStatus Status
        {
            get => _task.Status;
            set
            {
                _task.Status = value;
                RaisePropertyChanged();
            }
        }

        public bool IsEditing
        {
            get => _isEditing;
            set => SetProperty(ref _isEditing, value);
        }

        public KanbanTask Model => _task;
    }
} 