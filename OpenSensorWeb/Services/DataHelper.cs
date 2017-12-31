using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using OpenSensorWeb.Models;
using Newtonsoft.Json;
using System.Text;

namespace OpenSensorWeb.Services
{
    public class DataHelper
    {
        OpenMonitorEntities ome = new OpenMonitorEntities();


        #region ##Singleton##
        private static DataHelper _instance;
        private DataHelper() { }

        public static DataHelper Instance
        {
            get
            {
                if (_instance == null)
                {
                    _instance = new DataHelper();
                }
                return _instance;
            }
        }

        #endregion

        public string GetJSONSensorValue(int sensorModuleId, int lastXValues)
        {
            List<OpenMonitorValue> valueList = new List<OpenMonitorValue>();
            valueList = ome.OpenMonitorValue.Where(x => x.ModuleId == sensorModuleId).OrderByDescending(x => x.CreatedDate).Take(lastXValues).ToList();


            var json = JsonConvert.SerializeObject(valueList);
            string jsonString = json.ToString();

            if (valueList.Any())
            {
                return jsonString;
            }

            return string.Empty;
        }
        

    }
}