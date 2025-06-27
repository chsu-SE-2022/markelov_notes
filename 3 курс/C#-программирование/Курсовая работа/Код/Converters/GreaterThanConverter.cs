using System;
using System.Globalization;
using System.Windows.Data;

namespace TaskManager.Converters
{
    public class GreaterThanConverter : IValueConverter
    {
        public object Convert(object value, Type targetType, object parameter, CultureInfo culture)
        {
            if (value == null || parameter == null)
                return false;

            if (value is int intValue && parameter is string stringParameter)
            {
                if (int.TryParse(stringParameter, out int compareValue))
                {
                    return intValue > compareValue;
                }
            }

            return false;
        }

        public object ConvertBack(object value, Type targetType, object parameter, CultureInfo culture)
        {
            throw new NotImplementedException();
        }
    }
} 