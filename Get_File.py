import time
import datetime
import requests
import csv
import os
from lxml import html
import xlrd
import webbrowser
import selenium
from selenium import webdriver
from selenium.webdriver.chrome.options import Options
from selenium.webdriver.common.keys import Keys

clear = lambda: os.system('cls')
now = datetime.datetime.now()

def csv_from_excel(excel_file):
    workbook = xlrd.open_workbook(excel_file)
    all_worksheets = workbook.sheet_names()
    for worksheet_name in all_worksheets:
        worksheet = workbook.sheet_by_name(worksheet_name)
        with open('{}.csv'.format(worksheet_name), 'w') as your_csv_file:
            wr = csv.writer(your_csv_file, quoting=csv.QUOTE_ALL)
            for rownum in range(worksheet.nrows):
                wr.writerow([str(entry).encode("utf-8") for entry in worksheet.row_values(rownum)])

def get_file(path_file, path_ecar, out_path):
    ## From now we start to connect
    path_file = ''.join(path_file)
    if os.path.exists(path_file):
        os.remove(path_file)
        print("Fichier supprimé, le nouveau va être téléchargé ...")
    else:
        print("Encours inexistant, préparation du téléchargement")

    out_path = ''.join(out_path)
    # Using Chrome to access web
    chrome_options = Options()
    chrome_options.add_experimental_option("prefs", {
      "download.default_directory": "/path/to/download/dir",
      "download.prompt_for_download": False,})
    chrome_options.add_argument("--headless")
    driver = webdriver.Chrome(options = chrome_options)
    driver.command_executor._commands["send_command"] = ("POST", '/session/$sessionId/chromium/send_command')

    params = {'cmd': 'Page.setDownloadBehavior', 'params': {'behavior': 'allow', 'downloadPath': r'C:\Users\steven.mortier\Downloads'}}
    command_result = driver.execute("send_command", params)
    #Headless + dl c'est chaud A revoir
    
    # Open the website
    driver.get(path_ecar)
    # Select password box
    try:
        pass_box = driver.find_element_by_name('j_password')
    except:
        print("L'adresse ecar semble incorrect, la voici :", path_ecar)
        driver.quit()
        return 0
    # Equivalent Outcome! 
    id_box = driver.find_element_by_id('j_username')
    # Send id information
    id_box.send_keys(usernameecar)
    # Send password
    pass_box.send_keys(mdpecar)
    pass_box.send_keys(Keys.ENTER)
    driver.get(path_ecar)
    try:
        excel_button = driver.find_elements_by_xpath('//*[@id="content"]/table/tbody/tr[5]/td/div/a[5]/img')[0] #--> Xpath of the excel button
        excel_button.click()
        print("identification réussie")
    except:
        print("Les identifiants spécifiés ne sont pas correct !")
        driver.quit()
        return 0
    #print("DEBUG = ", os.path.isfile("C:/Users/steven.mortier/Downloads/encoursTRP160119.xls"))
    driver.get("http://gcav037:82/eCar/transport/planification/exportExcel.encoursTransport.do") # Link to Download the file
    print("Téléchargement de l'encours")
    while (os.path.isfile(path_file) is False): #check DL of file
        time.sleep(0.5)
    driver.quit()
    return 1

def occurance(path_file, path_ecar, out_path):
    done = 0
    done = get_file(path_file, path_ecar, out_path)
    if done != 0 :
        print("Fichier téléchargé")
        return 1

def get_date():
    day = now.day
    month = now.month
    year = now.year
    if (day < 10):
        day = "0" , str(day)
        day = ''.join(day)
    if (month < 10) :
        month = "0", str(month)
        month = ''.join(month)
    path = str(day), str(month), str(year)[2:]
    return (''.join(path))
    

if __name__ == '__main__':
    logs_file = open("Logs.txt", "r")
    logs_content = logs_file.readlines()
    path_ecar = logs_content[0]
    #print(path_ecar)
    session_name = logs_content[1] #input("Nom de session Windows : ")
    session_name = session_name[:-1]
    print("Nom de session : ",session_name)
    usernameecar = logs_content[2] #input("login Ecar : ")
    usernameecar = usernameecar[:-1]
    print("ID Ecar : ", usernameecar)
    mdpecar = logs_content[3] #input("Mot de passe Ecar : ")
    print("Mot de passe Ecar", mdpecar)
    date_path = get_date() #Get the right date format for the path
    out_path = "C:/Users/", session_name, "/Downloads"
    path_file = "C:/Users/", session_name, "/Downloads/encoursTRP"
    path_file = ''.join(path_file)
    path_file = path_file, date_path, ".xls"
    path_file = ''.join(path_file)
    counter = 20 #Iteration number
    maxi = counter #Iteration max constant
    check_dir_path = "C:/Users/", session_name, "/Downloads"
    check_dir_path = ''.join(check_dir_path) #strjoin a tuple
    print(check_dir_path)
    if (os.path.isdir(check_dir_path)): #check if the directory exist
        print("Le nom de session semble correct")
    else:
        print("Le nom de session semble invalide")
        counter = 0
    #print("Nous somme le ", now.day,"/", now.month, "/", now.year)
    while(counter != 0):
        if (occurance(path_file, path_ecar, out_path) == 1):
            counter = counter - 1
            print("------- étape " , (maxi - counter) ,"/", maxi," -------")
            csv_from_excel(path_file)
            if (counter > 0):
                time.sleep(60)
            clear()
            print("Opération términée")
        else:
            print("Le programme va quitter ...")
            counter = 0
    logs_file.close()
