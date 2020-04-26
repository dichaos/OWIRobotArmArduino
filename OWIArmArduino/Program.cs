﻿using System;
using System.IO.Ports;
using System.Linq;
using HidSharp;
using HidSharp.Reports;
using HidSharp.Reports.Input;
using HidSharp.Utility;

namespace OWIArmArduino
{
    class Program
    {
        public static SerialPort SerialPort { get; set; }
        static void WriteDeviceItemInputParserResult(DeviceItemInputParser parser)
        {
            while (parser.HasChanged)
            {
                var changedIndex = parser.GetNextChangedIndex();
                var previousDataValue = parser.GetPreviousValue(changedIndex);
                var dataValue = parser.GetValue(changedIndex);

                var y = (Usage) dataValue.Usages.FirstOrDefault();
                var value = (int)dataValue.GetPhysicalValue();
                
                Console.WriteLine($"{(Usage) dataValue.Usages.FirstOrDefault()}: {previousDataValue.GetPhysicalValue()} -> {dataValue.GetPhysicalValue()}");

                switch (y)
                {
                    case Usage.GenericDesktopY:
                        if (value == 255)SerialPort.Write(BitConverter.GetBytes(3),0,1);
                        if (value == 0)SerialPort.Write(BitConverter.GetBytes(4),0,1);
                        break;
                    case Usage.GenericDesktopX:
                        if (value == 255)SerialPort.Write(BitConverter.GetBytes(1),0,1);
                        if (value == 0)SerialPort.Write(BitConverter.GetBytes(2),0,1);
                        break;
                    case Usage.Button1:
                        if (value==1)SerialPort.Write(BitConverter.GetBytes(5),0,1);
                        
                        break;
                    case Usage.Button2:
                        if (value==1)SerialPort.Write(BitConverter.GetBytes(6),0,1);
                        break;
                    case Usage.Button3:
                        if (value==1)SerialPort.Write(BitConverter.GetBytes(7),0,1);
                        break;
                    case Usage.Button4:
                        if (value==1)SerialPort.Write(BitConverter.GetBytes(8),0,1);
                        break;
                    default:
                        break;    
                }
            }
        }

        static void Main(string[] args)
        {
            SerialPort = new SerialPort("COM3")
            {
                BaudRate = 9600,
                Parity = Parity.None,
                StopBits = StopBits.One,
                DataBits = 8,
                Handshake = Handshake.None
            };
            
            SerialPort.Open();
            
            HidSharpDiagnostics.EnableTracing = true;
            HidSharpDiagnostics.PerformStrictChecks = true;

            var list = DeviceList.Local;
            var hidDeviceList = list.GetHidDevices().ToArray();

            var device = hidDeviceList.SingleOrDefault(x => x.ProductName.Trim().Equals("usb gamepad"));

            device.TryOpen(out HidStream hidStream);

            var inputReportBuffer = new byte[device.GetMaxInputReportLength()];
            var reportDescriptor = device.GetReportDescriptor();
            var inputReceiver = reportDescriptor.CreateHidDeviceInputReceiver();

            foreach (var deviceItem in reportDescriptor.DeviceItems)
            {
                var inputParser = deviceItem.CreateDeviceItemInputParser();
                
                inputReceiver.Received += (sender, e) =>
                {
                    while (inputReceiver.TryRead(inputReportBuffer, 0, out Report report))
                    {
                        if (inputParser.TryParseReport(inputReportBuffer, 0, report))
                        {
                            WriteDeviceItemInputParserResult(inputParser);
                        }
                    }
                };
                inputReceiver.Start(hidStream);
            }

            Console.WriteLine("Press a key to exit...");
            Console.ReadKey();
        }
    }
}