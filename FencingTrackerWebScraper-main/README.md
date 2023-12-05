# FencingTrackerWebScraper
Backend for Fencing Tracker Web Scraper

Utilizes BeautifulSoup Library to scrape user data into .csv format to be utilized by a multitude of different use cases

SETUP/INSTALL:
1. install BeautifulSoup (pip3 install beautifulsoup)
2. install requests (pip3 install requests)


Node structure (Visualizations Sake):
  NAME
  CLUB AFFILIATION

  All-time Win/Loss Statistics (Array Implementation):
    Wins
    Losses
    Win Ratio
    Pool Wins
    Pool Losses
    Pool Win Ratio
    DE Wins
    DE Losses
    DE Ratio

  Competition Data (Map/Dictionary Implementation, two keys (name and competition name):
    Name of Competition
    Date of Competition
    Event
    Placing in Competition
    BOUT DATA
      Opponent
      Win/Loss of Bout
      Opponent's Club

Devlog:
-Webscraper is complete for up to 997 individuals. Need to bugfix PullLargestClubs to be able to scrape the entirety of the webpage 
