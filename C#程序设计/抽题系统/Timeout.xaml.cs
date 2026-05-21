using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Shapes;

namespace WpfApp1
{
    /// <summary>
    /// Timeout.xaml 的交互逻辑
    /// </summary>
    public partial class Timeout : Window
    {
        MainWindow mw;
        int timeout = 60;
        public Timeout(int timeout, MainWindow mw)
        {
            this.mw = mw;
            this.timeout = timeout;
            InitializeComponent();
            TimeoutTextBox.Text = timeout.ToString();
        }

        private void Button_Click(object sender, RoutedEventArgs e)
        {
            int timeout = 60;
            if (!String.IsNullOrEmpty(TimeoutTextBox.Text)) 
            {
                timeout = int.Parse(TimeoutTextBox.Text);
            }
            mw.setTimeout(timeout);
            this.Close();
        }
    }
}
