using Prism.DryIoc;
using Prism.Ioc;
using System;
using System.Windows;
using System.Windows.Threading;
using TaskManager.Data;
using TaskManager.Services;
using TaskManager.Views;
using Microsoft.EntityFrameworkCore;
using TaskManager.ViewModels;

namespace TaskManager
{
    // Главный класс приложения
    public partial class App : PrismApplication
    {
        public App()
        {
            DispatcherUnhandledException += App_DispatcherUnhandledException;
            AppDomain.CurrentDomain.UnhandledException += CurrentDomain_UnhandledException;
        }

        // Обработчик необработанных исключений в UI потоке
        private void App_DispatcherUnhandledException(object sender, DispatcherUnhandledExceptionEventArgs e)
        {
            MessageBox.Show($"Необработанное исключение: {e.Exception.Message}\n\nПодробности: {e.Exception.StackTrace}",
                "Ошибка", MessageBoxButton.OK, MessageBoxImage.Error);
            e.Handled = true;
        }

        // Обработчик необработанных исключений в других потоках
        private void CurrentDomain_UnhandledException(object sender, UnhandledExceptionEventArgs e)
        {
            if (e.ExceptionObject is Exception ex)
            {
                MessageBox.Show($"Критическая ошибка: {ex.Message}\n\nПодробности: {ex.StackTrace}",
                    "Критическая ошибка", MessageBoxButton.OK, MessageBoxImage.Error);
            }
        }

        // Создание главного окна приложения
        protected override Window CreateShell()
        {
            try
            {
                var window = Container.Resolve<MainWindow>();
                if (window == null)
                {
                    throw new Exception("Не удалось создать главное окно");
                }
                return window;
            }
            catch (Exception ex)
            {
                MessageBox.Show($"Ошибка при создании главного окна: {ex.Message}",
                    "Ошибка", MessageBoxButton.OK, MessageBoxImage.Error);
                Current.Shutdown();
                return null;
            }
        }

        // Регистрация сервисов и зависимостей
        protected override void RegisterTypes(IContainerRegistry containerRegistry)
        {
            try
            {
                // Настройка подключения к базе данных
                var dbPath = System.IO.Path.Combine(Environment.GetFolderPath(Environment.SpecialFolder.ApplicationData), "TaskManager", "TaskManager.db");
                System.IO.Directory.CreateDirectory(System.IO.Path.GetDirectoryName(dbPath));

                var options = new DbContextOptionsBuilder<TaskManagerDbContext>()
                    .UseSqlite($"Data Source={dbPath}")
                    .EnableSensitiveDataLogging()
                    .Options;

                // Регистрация контекста базы данных
                containerRegistry.RegisterInstance(options);
                containerRegistry.Register<TaskManagerDbContext>();

                // Регистрация сервиса для работы с задачами
                containerRegistry.RegisterSingleton<ITaskService, TaskService>();
                containerRegistry.RegisterSingleton<IDialogService, DialogService>();
                containerRegistry.RegisterSingleton<INotificationService, NotificationService>();
            }
            catch (Exception ex)
            {
                MessageBox.Show($"Ошибка при регистрации сервисов: {ex.Message}",
                    "Ошибка", MessageBoxButton.OK, MessageBoxImage.Error);
                throw;
            }
        }

        // Инициализация приложения
        protected override async void OnStartup(StartupEventArgs e)
        {
            try
            {
                base.OnStartup(e);
                
                var context = Container.Resolve<TaskManagerDbContext>();
                await context.Database.EnsureCreatedAsync();

                // Загрузка данных будет происходить в обработчике Loaded окна MainWindow
                var mainWindow = Container.Resolve<MainWindow>();
                // var viewModel = mainWindow.DataContext as MainWindowViewModel;
                // if (viewModel != null)
                // {
                //     await viewModel.InitializeAsync();
                // }
            }
            catch (Exception ex)
            {
                MessageBox.Show($"Ошибка при инициализации приложения: {ex.Message}",
                    "Ошибка", MessageBoxButton.OK, MessageBoxImage.Error);
                Current.Shutdown();
            }
        }

        protected override void ConfigureViewModelLocator()
        {
            base.ConfigureViewModelLocator();
        }
    }
} 