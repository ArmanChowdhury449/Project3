from bs4 import BeautifulSoup
import csv
import pandas
import requests
import os

#Pulls the name data from the top 50 clubs on FencingTracker
def pullLargestClubs(outputCSV):
    #Header element necessary for website access
    headers = {
        'User-Agent': 'Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/91.0.4472.124 Safari/537.36',
    }
    url = "https://www.fencingtracker.com/largestclubs"
    finalLinks = []

    #Layered hyperlinks from the starting URL. Below shows hyperlink path for data collection:
    #Largest Clubs -> Club's rating -> Club's Members -> Individual Member Info -> /history to access Bout History
    # 4 Hyperlinks to move through Club's Members needs to loop through all members

    response = requests.get(url, headers=headers)
    doc = BeautifulSoup(response.text, 'html.parser')

    #Pulls all hyperlink data from the url webpage; Slices the top 500
    clubLinks = [link['href'] for link in doc.find_all('a', href=True)][:500]

    for clubLink in clubLinks:
        #First layer; Club URL from largestClubs page
        clubURL = "https://fencingtracker.com" + clubLink
        clubResponse = requests.get(clubURL, headers=headers)
        clubSoup = BeautifulSoup(clubResponse.text, 'html.parser')

        #Second Layer; Club Ratings Page from Club URL
        ratingLinks = clubSoup.find_all('a')
        
        for ratingLink in ratingLinks:
            href = ratingLink.get('href')

            #Cleaning function; removes the /topclubs/... hyperlink since it is a repetitive call; Will pretty much loop forever if branched down
            if href == "/topclubs/epee" or href == "/topclubs/foil" or href == "/topclubs/saber" or href == "#":
                continue

            #Third Layer; Names Page from Club Ratings Page
            if href is not None:
                clubMemebersPage = "https://fencingtracker.com" + href
                pageResponse = requests.get(clubMemebersPage, headers=headers)
                membersSoup = BeautifulSoup(pageResponse.text, "html.parser")

                membersLinks = membersSoup.find_all('a')

                for memberLink in membersLinks:
                    href = memberLink.get('href')
                    print(str(href))

                    if href is not None and href.startswith("/p/"):
                        finalLinks.append(href)
                        length = len(finalLinks)
                        print(str(length))

                #FOURTH LAYER IS UNNECESSARY SINCE WE CAN JUST APPEND /history LATER

                #Output to CSV file
    with open(outputCSV, 'w', newline='') as csvfile:
        writer = csv.writer(csvfile)
        writer.writerow(['URL TAG'])
        for link in finalLinks:
            writer.writerow([link])
            


#Main scraping method; Pulls URLs in .csv created in pullLinks to generate data from FencingTracker
def scrapeAndExport(inputFile, url, outputFile):
    #Header element necessary for website access
    headers = {
        'User-Agent': 'Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/91.0.4472.124 Safari/537.36',
    }

    with open(inputFile, 'r') as csvfile:
        csvReader = csv.reader(csvfile)
        next(csvReader)
        
        for row in csvReader:

            rowContent = ''.join(row)
            urlExtension = url + rowContent + "/history"
            print(urlExtension)

            #BeautifulSoup Basic Script
            result = requests.get(urlExtension, headers=headers)
            doc = BeautifulSoup(result.text, "html.parser")

            #Variables for easier assignment
            #Pulls NAME; Finds the first item labeled under h1
            NAME = doc.find('h1')

            #Pulls CLUB AFFILIATIONS
            CLUBS = doc.find('h2')

            #Pulls Win/Loss Statistics Table
            statsTable = doc.find('table')

            #Stats Variable Creation
            rows = statsTable.find_all('tr')

            ATWins = ""
            ATLosses = ""
            winRatio = ""
            poolWins = ""
            poolLosses = ""
            poolWinRatio = ""
            DEWins = ""
            DELosses = ""
            DEWinRatio = ""

            #Placeholders for the stats; Shows variable to index representation
            statsArray = [
                NAME.text, #.text is needed to remove HTML tags
                CLUBS.text,
                ATWins,
                ATLosses,
                winRatio,
                poolWins,
                poolLosses,
                poolWinRatio,
                DEWins,
                DELosses,
                DEWinRatio
            ]

            #Proper parsing for all Variables; Populates statsArray
            index = 2
            for row in rows:
                cells = row.find_all('td')
                if cells:
                    last_cell = cells[-1]
                    statsArray[index] = last_cell.text
                    index += 1

            print("Appending is complete")
            #Reset index for tidiness
            index = 0

            #.csv file creation
            with open(outputFile, 'a', newline='') as csvfile:
                writer = csv.writer(csvfile)
                if os.path.getsize(outputFile) == 0:
                    writer.writerow(['NAME', 'CLUBS', 'ATWins', 'ATLosses', 'winRatio', 'poolWins', 'poolLosses', 'poolWinRatio', 'DEWins', 'DELosses', 'DEWinRatio'])
                writer.writerow(statsArray)

#Example Call 
scrapeAndExport('/Users/michelecraig/Desktop/My Project Files/Python/FencingTrackerCSVOutputs/URLInputs.csv', 'https://www.fencingtracker.com', '/Users/michelecraig/Desktop/My Project Files/Python/FencingTrackerCSVOutputs/output.csv')

#pullLargestClubs('/Users/michelecraig/Desktop/My Project Files/Python/FencingTrackerCSVOutputs/URLInputs.csv')
#print("complete")