using Prism.Commands;
using Prism.Mvvm;
using System;
using System.Collections.ObjectModel;
using System.Linq;
using System.Threading.Tasks;
using TaskManager.Models;
using TaskManager.Services;
using System.Windows.Input;
using TaskManager.Behaviors;

namespace TaskManager.ViewModels
{
    // Основной класс для управления задачами в главном окне
    public class MainWindowViewModel : BindableBase, IDragDropHandler
    {
        // Сервис для работы с задачами
        private readonly ITaskService _taskService;
        private readonly IDialogService _dialogService;
        private readonly INotificationService _notificationService;

        // Список задач в бэклоге
        private ObservableCollection<KanbanTaskViewModel> _backlogTasks;
        public ObservableCollection<KanbanTaskViewModel> BacklogTasks
        {
            get => _backlogTasks;
            set => SetProperty(ref _backlogTasks, value);
        }

        // Список запрошенных задач
        private ObservableCollection<KanbanTaskViewModel> _requestTasks;
        public ObservableCollection<KanbanTaskViewModel> RequestTasks
        {
            get => _requestTasks;
            set => SetProperty(ref _requestTasks, value);
        }

        // Список выбранных задач
        private ObservableCollection<KanbanTaskViewModel> _selectedTasks;
        public ObservableCollection<KanbanTaskViewModel> SelectedTasks
        {
            get => _selectedTasks;
            set => SetProperty(ref _selectedTasks, value);
        }

        // Список задач в работе
        private ObservableCollection<KanbanTaskViewModel> _inProgressTasks;
        public ObservableCollection<KanbanTaskViewModel> InProgressTasks
        {
            get => _inProgressTasks;
            set => SetProperty(ref _inProgressTasks, value);
        }

        // Список выполненных задач
        private ObservableCollection<KanbanTaskViewModel> _completedTasks;
        public ObservableCollection<KanbanTaskViewModel> CompletedTasks
        {
            get => _completedTasks;
            set => SetProperty(ref _completedTasks, value);
        }

        private KanbanTaskViewModel _editingTask;
        public KanbanTaskViewModel EditingTask
        {
            get => _editingTask;
            set => SetProperty(ref _editingTask, value);
        }

        private bool _isEditing;
        public bool IsEditing
        {
            get => _isEditing;
            set => SetProperty(ref _isEditing, value);
        }

        // Команды для добавления задач в разные колонки
        public ICommand AddBacklogTaskCommand { get; private set; }
        public ICommand AddRequestTaskCommand { get; private set; }
        public ICommand AddSelectedTaskCommand { get; private set; }
        public ICommand AddInProgressTaskCommand { get; private set; }
        public ICommand AddCompletedTaskCommand { get; private set; }
        public ICommand EditTaskCommand { get; private set; }
        public ICommand SaveTaskCommand { get; private set; }
        public ICommand CancelEditCommand { get; private set; }
        public ICommand DeleteTaskCommand { get; private set; }

        // Конструктор с инициализацией команд и загрузкой задач
        public MainWindowViewModel(ITaskService taskService, IDialogService dialogService, INotificationService notificationService)
        {
            _taskService = taskService ?? throw new ArgumentNullException(nameof(taskService));
            _dialogService = dialogService ?? throw new ArgumentNullException(nameof(dialogService));
            _notificationService = notificationService ?? throw new ArgumentNullException(nameof(notificationService));

            InitializeCollections();
            InitializeCommands();
        }

        private void InitializeCollections()
        {
            BacklogTasks = new ObservableCollection<KanbanTaskViewModel>();
            RequestTasks = new ObservableCollection<KanbanTaskViewModel>();
            SelectedTasks = new ObservableCollection<KanbanTaskViewModel>();
            InProgressTasks = new ObservableCollection<KanbanTaskViewModel>();
            CompletedTasks = new ObservableCollection<KanbanTaskViewModel>();

            // Подписываемся на изменения коллекций для обновления счетчиков
            BacklogTasks.CollectionChanged += (s, e) => RaisePropertyChanged(nameof(BacklogTaskCount));
            RequestTasks.CollectionChanged += (s, e) => RaisePropertyChanged(nameof(RequestTaskCount));
            SelectedTasks.CollectionChanged += (s, e) => RaisePropertyChanged(nameof(SelectedTaskCount));
            InProgressTasks.CollectionChanged += (s, e) => RaisePropertyChanged(nameof(InProgressTaskCount));
            CompletedTasks.CollectionChanged += (s, e) => RaisePropertyChanged(nameof(CompletedTaskCount));
        }

        private void InitializeCommands()
        {
            AddBacklogTaskCommand = new DelegateCommand(() => CreateNewTask(KanbanTaskStatus.Backlog));
            AddRequestTaskCommand = new DelegateCommand(() => CreateNewTask(KanbanTaskStatus.Request));
            AddSelectedTaskCommand = new DelegateCommand(() => CreateNewTask(KanbanTaskStatus.Selected));
            AddInProgressTaskCommand = new DelegateCommand(() => CreateNewTask(KanbanTaskStatus.InProgress));
            AddCompletedTaskCommand = new DelegateCommand(() => CreateNewTask(KanbanTaskStatus.Completed));
            EditTaskCommand = new DelegateCommand<KanbanTaskViewModel>(StartEditingTask);
            SaveTaskCommand = new DelegateCommand<KanbanTaskViewModel>(async (task) => await SaveTaskAsync(task));
            CancelEditCommand = new DelegateCommand<KanbanTaskViewModel>(CancelEditing);
            DeleteTaskCommand = new DelegateCommand<KanbanTaskViewModel>(async (task) => await DeleteTaskAsync(task));
        }

        public async Task InitializeAsync()
        {
            await LoadTasksAsync();
        }

        private void CreateNewTask(KanbanTaskStatus status)
        {
            var newTask = new KanbanTask
            {
                Status = status,
                Title = "",
                Description = "",
                CreatedAt = DateTime.Now
            };
            var taskViewModel = new KanbanTaskViewModel(newTask) { IsEditing = true };
            GetCollectionForStatus(status).Insert(0, taskViewModel);
        }

        private void StartEditingTask(KanbanTaskViewModel task)
        {
            if (task == null) return;
            task.IsEditing = true;
        }

        private async Task SaveTaskAsync(KanbanTaskViewModel task)
        {
            try
            {
                if (task == null) return;

                if (string.IsNullOrWhiteSpace(task.Title))
                {
                    _notificationService.ShowNotification("Заголовок задачи не может быть пустым!");
                    return;
                }

                if (task.Id == 0)
                {
                    // Новая задача
                    var addedTask = await _taskService.AddTaskAsync(task.Model);
                    var collection = GetCollectionForStatus(task.Status);
                    var index = collection.IndexOf(task);
                    var newTaskViewModel = new KanbanTaskViewModel(addedTask);
                    collection[index] = newTaskViewModel;
                }
                else
                {
                    // Обновление существующей задачи
                    await _taskService.UpdateTaskAsync(task.Model);
                }

                task.IsEditing = false;
            }
            catch (Exception ex)
            {
                _dialogService.ShowError($"Ошибка при сохранении задачи: {ex.Message}");
            }
        }

        private void CancelEditing(KanbanTaskViewModel task)
        {
            if (task == null) return;

            if (task.Id == 0) // Новая задача
            {
                var collection = GetCollectionForStatus(task.Status);
                collection.Remove(task);
            }
            else
            {
                task.IsEditing = false;
            }
        }

        private async Task DeleteTaskAsync(KanbanTaskViewModel task)
        {
            try
            {
                if (task == null || task.Id == 0) return;

                await _taskService.DeleteTaskAsync(task.Id);
                var collection = GetCollectionForStatus(task.Status);
                collection.Remove(task);
            }
            catch (Exception ex)
            {
                _dialogService.ShowError($"Ошибка при удалении задачи: {ex.Message}");
            }
        }

        // Перемещение задачи в другую колонку
        public async Task MoveTaskAsync(KanbanTaskViewModel task, KanbanTaskStatus newStatus)
        {
            if (task == null) return;

            try
            {
                task.Status = newStatus;
                await _taskService.UpdateTaskAsync(task.Model);

                BacklogTasks.Remove(task);
                RequestTasks.Remove(task);
                SelectedTasks.Remove(task);
                InProgressTasks.Remove(task);
                CompletedTasks.Remove(task);

                GetCollectionForStatus(newStatus).Add(task);
            }
            catch (Exception ex)
            {
                _dialogService.ShowError($"Ошибка при перемещении задачи: {ex.Message}");
                await LoadTasksAsync();
            }
        }

        // Получение коллекции задач по статусу
        private ObservableCollection<KanbanTaskViewModel> GetCollectionForStatus(KanbanTaskStatus status)
        {
            return status switch
            {
                KanbanTaskStatus.Backlog => BacklogTasks,
                KanbanTaskStatus.Request => RequestTasks,
                KanbanTaskStatus.Selected => SelectedTasks,
                KanbanTaskStatus.InProgress => InProgressTasks,
                KanbanTaskStatus.Completed => CompletedTasks,
                _ => BacklogTasks
            };
        }

        // Загрузка всех задач из базы данных
        public async Task LoadTasksAsync()
        {
            try
            {
                var loadTasks = new[]
                {
                    _taskService.GetTasksByStatusAsync(KanbanTaskStatus.Backlog),
                    _taskService.GetTasksByStatusAsync(KanbanTaskStatus.Request),
                    _taskService.GetTasksByStatusAsync(KanbanTaskStatus.Selected),
                    _taskService.GetTasksByStatusAsync(KanbanTaskStatus.InProgress),
                    _taskService.GetTasksByStatusAsync(KanbanTaskStatus.Completed)
                };

                var results = await Task.WhenAll(loadTasks);

                // Очищаем существующие коллекции перед добавлением новых данных
                BacklogTasks.Clear();
                RequestTasks.Clear();
                SelectedTasks.Clear();
                InProgressTasks.Clear();
                CompletedTasks.Clear();

                // Добавляем загруженные задачи в коллекции
                foreach (var task in results[0].Select(t => new KanbanTaskViewModel(t)))
                {
                    BacklogTasks.Add(task);
                }
                foreach (var task in results[1].Select(t => new KanbanTaskViewModel(t)))
                {
                    RequestTasks.Add(task);
                }
                foreach (var task in results[2].Select(t => new KanbanTaskViewModel(t)))
                {
                    SelectedTasks.Add(task);
                }
                foreach (var task in results[3].Select(t => new KanbanTaskViewModel(t)))
                {
                    InProgressTasks.Add(task);
                }
                foreach (var task in results[4].Select(t => new KanbanTaskViewModel(t)))
                {
                    CompletedTasks.Add(task);
                }
            }
            catch (Exception ex)
            {
                _dialogService.ShowError($"Ошибка при загрузке задач: {ex.Message}");
            }
        }

        public void OnDragStart(object item)
        {
            // Можно добавить визуальную обратную связь при начале перетаскивания
        }

        public void OnDragEnd(object item)
        {
            // Можно добавить визуальную обратную связь при окончании перетаскивания
        }

        public async void OnDrop(object item, KanbanTaskStatus targetStatus)
        {
            if (item is KanbanTaskViewModel task && task.Status != targetStatus)
            {
                await MoveTaskAsync(task, targetStatus);
            }
        }

        public void OnItemDoubleClick(object item)
        {
            if (item is KanbanTaskViewModel task)
            {
                StartEditingTask(task);
            }
        }

        // Коллекция активных уведомлений для привязки в View
        public ObservableCollection<NotificationViewModel> Notifications => (_notificationService as NotificationService)?.Notifications;

        // Свойства для счетчиков задач (отображаются в заголовках колонок)
        public int BacklogTaskCount => BacklogTasks.Count;
        public int RequestTaskCount => RequestTasks.Count;
        public int SelectedTaskCount => SelectedTasks.Count;
        public int InProgressTaskCount => InProgressTasks.Count;
        public int CompletedTaskCount => CompletedTasks.Count;
    }
} 