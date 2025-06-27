using System;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Input;
using System.Windows.Media;
using Microsoft.Xaml.Behaviors;
using TaskManager.Models;

namespace TaskManager.Behaviors
{
    public interface IDragDropHandler
    {
        void OnDragStart(object item);
        void OnDragEnd(object item);
        void OnDrop(object item, KanbanTaskStatus targetStatus);
        void OnItemDoubleClick(object item);
    }

    public class DragDropBehavior : Behavior<ListView>
    {
        public static readonly DependencyProperty IsEnabledProperty =
            DependencyProperty.RegisterAttached(
                "IsEnabled",
                typeof(bool),
                typeof(DragDropBehavior),
                new PropertyMetadata(false, OnIsEnabledChanged));

        public static bool GetIsEnabled(DependencyObject obj)
        {
            return (bool)obj.GetValue(IsEnabledProperty);
        }

        public static void SetIsEnabled(DependencyObject obj, bool value)
        {
            obj.SetValue(IsEnabledProperty, value);
        }

        private static void OnIsEnabledChanged(DependencyObject d, DependencyPropertyChangedEventArgs e)
        {
            if (d is ListView listView)
            {
                var behavior = new DragDropBehavior();
                if ((bool)e.NewValue)
                {
                    Interaction.GetBehaviors(listView).Add(behavior);
                }
                else
                {
                    var behaviors = Interaction.GetBehaviors(listView);
                    for (int i = behaviors.Count - 1; i >= 0; i--)
                    {
                        if (behaviors[i] is DragDropBehavior)
                        {
                            behaviors.RemoveAt(i);
                        }
                    }
                }
            }
        }

        private Point _startPoint;
        private bool _isDragging;
        private object _draggedItem;

        protected override void OnAttached()
        {
            base.OnAttached();
            AssociatedObject.PreviewMouseLeftButtonDown += ListView_PreviewMouseLeftButtonDown;
            AssociatedObject.MouseMove += ListView_MouseMove;
            AssociatedObject.Drop += ListView_Drop;
            AssociatedObject.MouseDoubleClick += ListView_MouseDoubleClick;
            AssociatedObject.AllowDrop = true;
        }

        protected override void OnDetaching()
        {
            base.OnDetaching();
            AssociatedObject.PreviewMouseLeftButtonDown -= ListView_PreviewMouseLeftButtonDown;
            AssociatedObject.MouseMove -= ListView_MouseMove;
            AssociatedObject.Drop -= ListView_Drop;
            AssociatedObject.MouseDoubleClick -= ListView_MouseDoubleClick;
        }

        private void ListView_PreviewMouseLeftButtonDown(object sender, MouseButtonEventArgs e)
        {
            _startPoint = e.GetPosition(null);
            var listView = sender as ListView;
            var item = FindAncestor<ListViewItem>((DependencyObject)e.OriginalSource);

            if (item != null)
            {
                _draggedItem = item.DataContext;
                _isDragging = true;

                if (AssociatedObject.DataContext is IDragDropHandler handler)
                {
                    handler.OnDragStart(_draggedItem);
                }
            }
        }

        private void ListView_MouseMove(object sender, MouseEventArgs e)
        {
            if (_isDragging && e.LeftButton == MouseButtonState.Pressed && _draggedItem != null)
            {
                Point mousePos = e.GetPosition(null);
                Vector diff = _startPoint - mousePos;

                if (Math.Abs(diff.X) > SystemParameters.MinimumHorizontalDragDistance ||
                    Math.Abs(diff.Y) > SystemParameters.MinimumVerticalDragDistance)
                {
                    var listView = sender as ListView;
                    var dragData = new DataObject("KanbanTask", _draggedItem);
                    DragDrop.DoDragDrop(listView, dragData, DragDropEffects.Move);
                    _isDragging = false;

                    if (AssociatedObject.DataContext is IDragDropHandler handler)
                    {
                        handler.OnDragEnd(_draggedItem);
                    }

                    _draggedItem = null;
                }
            }
        }

        private void ListView_Drop(object sender, DragEventArgs e)
        {
            if (e.Data.GetDataPresent("KanbanTask"))
            {
                var item = e.Data.GetData("KanbanTask");
                var targetListView = sender as ListView;
                var targetStatus = (KanbanTaskStatus)targetListView.Tag;

                if (item != null && AssociatedObject.DataContext is IDragDropHandler handler)
                {
                    handler.OnDrop(item, targetStatus);
                }
            }
        }

        private void ListView_MouseDoubleClick(object sender, MouseButtonEventArgs e)
        {
            if (AssociatedObject.SelectedItem != null && 
                AssociatedObject.DataContext is IDragDropHandler handler)
            {
                handler.OnItemDoubleClick(AssociatedObject.SelectedItem);
            }
        }

        private static T FindAncestor<T>(DependencyObject current) where T : DependencyObject
        {
            do
            {
                if (current is T ancestor)
                {
                    return ancestor;
                }
                current = VisualTreeHelper.GetParent(current);
            }
            while (current != null);
            return null;
        }
    }
}