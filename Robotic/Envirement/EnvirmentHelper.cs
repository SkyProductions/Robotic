using System;
using System.IO;

namespace Robotic.Envirement
{
    public class EnvirmentHelper
    {
        public static string RootFolder()
        {
            string rootFolder = Path.Combine(Environment.GetFolderPath(Environment.SpecialFolder.ApplicationData), "Kyocera");
            if (!Directory.Exists(rootFolder))
            {
                Directory.CreateDirectory(rootFolder);
            }

            return rootFolder;
        }


        public static string ProjectsFolder()
        {
            string rootFolder = RootFolder();
            string projectsPath = Path.Combine(rootFolder, "Projects");
            if (!Directory.Exists(projectsPath))
            {
                Directory.CreateDirectory(projectsPath);
            }

            return projectsPath;
        }

        public static string ProjectsDataPath()
        {
            string projectsFolder = ProjectsFolder();
            return Path.Combine(projectsFolder, "projects.json");
        }

        public static string GlobalDevicesFolder()
        {
            string rootFolder = RootFolder();
            string devicesPath = Path.Combine(rootFolder, "Devices");
            if (!Directory.Exists(devicesPath))
            {
                Directory.CreateDirectory(devicesPath);
            }

            return devicesPath;
        }

        public static string GlobalDevicesStorageFile()
        {
            string devicesFolder = GlobalDevicesFolder();
            return Path.Combine(devicesFolder, "global_devices.json");
        }

        public static string CreateProjectPath(string id, string name)
        {
            string rootFolder = ProjectsFolder();
            string projectFolder = string.Format("{0}.{1}",id,name);
            string projectPath = Path.Combine(rootFolder, projectFolder);

            if(!Directory.Exists(projectPath))
            {
                Directory.CreateDirectory(projectPath); 
            }

            return projectPath;
        }
    }
}
