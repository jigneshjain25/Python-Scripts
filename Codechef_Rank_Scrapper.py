from bs4 import BeautifulSoup
import urllib2

rankURL = "http://www.codechef.com/rankings/ACMAMR14"
page=urllib2.urlopen(rankURL)
soup = BeautifulSoup(page.read())

rank=0
for link in soup.find_all('a'):
    href = link.get('href')
    if "/users/acm" in href:
        rank=rank+1
        handle =  href[7:]
        page=urllib2.urlopen("http://www.codechef.com/"+href)
        subsoup = BeautifulSoup(page.read())
        cols = subsoup.findAll('td')
        teamName = cols[7].text
        colgName = cols[17].text
        print rank,",", teamName, ",", colgName,",", handle        
        #if rank==10:
        #   break
