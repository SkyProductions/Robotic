using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Robotic.Helper
{
    public class StepHelper
    {
        private static StepProxy _stepProxy = new StepProxy();
        

        public static void ConvertStepToObj(string setpFile, string objFile)
        {
            if (!_stepProxy.ExportStepToObj(setpFile, objFile))
            {
                return;
            }    
        }
    }
}
