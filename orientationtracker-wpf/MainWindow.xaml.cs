using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Globalization;
using System.IO.Ports;
using System.Linq;
using System.Text;
using System.Threading;
using System.Threading.Tasks;
using System.Windows;

using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Media.Media3D;
using System.Windows.Navigation;
using System.Windows.Shapes;
using HelixToolkit.Wpf;
using Newtonsoft.Json.Linq;

namespace graphicstest
{
    /// <summary>
    /// Interaction logic for MainWindow containing menu + 3D rotating object movements according to the COM7 port 
    /// </summary>
    public partial class MainWindow : Window
    {

        private SerialPort port { get; set; }
        private string data { get; set; }

        public MainWindow()
        {
            InitializeComponent();
            btnConnect.IsEnabled = true;
            btnClose.IsEnabled = false;

            // Get Serial Ports + add them to combobox
            var ports = SerialPort.GetPortNames();
            portMenu.Items.Clear();
            foreach(string comport in ports)
            {
                portMenu.Items.Add(comport);
                Trace.WriteLine(comport);
            }
            
            portMenu.SelectedIndex = 0;
            
        }

        private void connect_click(object sender, RoutedEventArgs e)
        {

            btnConnect.IsEnabled = false;
            btnClose.IsEnabled = true;

            try
            {
                port = new SerialPort();
                port.PortName = portMenu.Text;
                port.NewLine = "\r";
                port.Open();
                port.DataReceived += new System.IO.Ports.SerialDataReceivedEventHandler(data_received);
                status.Text = "Connected to " + port.PortName;
            } catch(Exception ex)
            {
                status.Text = ex.Message;
            }
        }

        private void disconnect_click(object sender, RoutedEventArgs e)
        {
            btnConnect.IsEnabled = true;
            btnClose.IsEnabled = false;
            // btnCalibrate.IsEnabled = false;

            try
            {
                if (port.IsOpen && port != null) port.Close();
                status.Text = "Closed connection with " + port.PortName;
                Trace.WriteLine($"disconnect button is clicked {e}");
            } catch(Exception exp)
            {
                Trace.WriteLine($"disconnect click + {exp}");
                return;
            }
        }

        private void data_received(System.Object sender, System.IO.Ports.SerialDataReceivedEventArgs e)
        {

            try
            {
                data = port.ReadLine();
            
                Application.Current.Dispatcher.InvokeAsync(new Action(() =>
                {
                    JObject parsedData;

                    try
                    {
                        parsedData = JObject.Parse(data);
                    }
                    catch (Exception e)
                    {
                        Trace.WriteLine($"parse error + {e}");
                        return;
                    }
                    
                    
                    Trace.Write($"{parsedData["x"]}, {parsedData["y"]}, {parsedData["z"]}"); // debugging purposes
                    input.Content = $"X: {parsedData["x"]} \t Y: {parsedData["y"]} \t Z: {parsedData["z"]}";
                    // rotate object
                    objectSensor.Transform = new MatrixTransform3D();
                    RotateX(Convert.ToDouble(parsedData["pitch"]));
                    RotateY(Convert.ToDouble(parsedData["roll"]));
                    
                }));
            } catch (Exception exp)
            {
                Trace.WriteLine($"data received lost connection + {exp}");
            }
        }

        private void RotateX(double angle)
        {
            var matrix = objectSensor.Transform.Value;
            matrix.Rotate(new Quaternion(new Vector3D(1, 0, 0), Convert.ToDouble(angle)));
            objectSensor.Transform = new MatrixTransform3D(matrix);
        }

        private void RotateY(double angle)
        {
            var matrix = objectSensor.Transform.Value;
            matrix.Rotate(new Quaternion(new Vector3D(0, 1, 0), Convert.ToDouble(angle)));
            objectSensor.Transform = new MatrixTransform3D(matrix);
        }

        private JObject getData(string data)
        {
            JObject parsedData;

            try
            {
                parsedData = JObject.Parse(data);
                return parsedData;
            }
            catch (Exception e)
            {
                Trace.WriteLine($"parse error + {e}");
                return null;
            }
        }
    }
}
