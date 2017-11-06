#Test file for scraping Thesaurus.com in an effort to build our own synsets
#as opposed to using nltk's wordnet.
#Scraping will be performed with beautifulsoup
#Author: Alec Frey
#Installation: MTSU
#Date: 3/16/2017


import requests
from bs4 import BeautifulSoup

#finds the synonyms of a passed keyword. THis function assumes the base
#search will come up with the correct POS. We will implement a better
#version later
def Syns(keyword , pos):
    
    #sets url for opening
    url = "http://www.thesaurus.com/browse/"
    newUrl = url + keyword

    #opens the url in beautifulsoup
    response = requests.get(newUrl)
    html = response.content
    soup = BeautifulSoup(html, "lxml")

    #creates an empty list for storing the words
    synonyms = []

    #creates a list to hold the tab numbers of the proper POS words
    tabs = []

    #parses the html for the code
    if soup is not None:
        synset = soup.find('div', attrs = {'id' : 'container'})
        if synset is not None:
            variations = synset.find('div', attrs = {'id': 'heading'}) #finds correct pos
            if variations is not None:
                words = variations.findAll('em')
                count = 0
                for word in words:
                    item = str(word)
                    item = item.split('>')
                    item = item[1]
                    item = item[:item.find('<')]
                    if item == pos:
                        tabs.append(count)
                    count += 1
            content = synset.find('div', attrs = {'id' : 'content'})
            if content is not None:
                for count in tabs:
                    classid = 'synonyms-' + str(count)
                    syns = content.find('div', attrs = {'id' : classid})
                    if syns is not None:
                        count = 0
                        relevancy = syns.find('div', attrs =  {'class' : 'relevancy-block'})
                        for syn in relevancy.findAll('li'):
                            data = str(syn)
                            index = data.find('browse') + 7
                            data = data[index:]
                            index = data.find('"')
                            data = data[:index]
                            if not data in synonyms:
                                synonyms.append(data)
                    count += 1

    synonyms = FixSpaces(synonyms)
    return synonyms
    


#this function will return all the synonyms of synonyms for they keywrod
#provided
def SynsOfSyns(keyword, partOfSpeech):

    #sets the first url for the scrape
    url = "http://www.thesaurus.com/browse/"
    count = 1
    newUrl = url + keyword + '/' + str(count)

    #opens the url in beautiful soup and checks if it is a valid website
    response = requests.get(newUrl)
    html = response.content
    soup = BeautifulSoup(html, "lxml")
    valid = CheckIfEnd(soup)

    #loops and take the data and stores in synonyms
    synonyms = []
    while not valid:

        #searches thesaurus.com for data
        synset = soup.find('div', attrs = {'id' : 'container'})
        content = synset.find('div', attrs = {'id' : 'content'})
        for item in content.findAll('div', attrs = { 'class': 'box syn_of_syns oneClick-area'}):
            pos = str(item.find('div', attrs = {'class' : 'def'}))
            pos = pos[17: pos.find('.')]
            if pos != partOfSpeech:
                continue
            for word in item.findAll('li'):
                data = str(word)
                data = data.split()
                data = data[2]
                location = data.find('browse')
                location += 7
                synonym = data[location:]
                synonym = synonym[:synonym.find('"')]

                if not synonym in synonyms and not synonym == keyword:
                    synonyms.append(synonym)
        
        #resets the url for next page
        count += 1
        newUrl = url + keyword + '/' + str(count)
        response = requests.get(newUrl)
        html = response.content
        soup = BeautifulSoup(html, "lxml")
        valid = CheckIfEnd(soup)

    synonyms = FixSpaces(synonyms)
    return synonyms
        


#checks the heading to determine if the search was invalid
#if invalid the heading is of form word/browse/word
#if valid it is of form word
def CheckIfEnd(soup):

    heading = str(soup.find('h1'))
    index = heading.find('browse')
    if index == -1:
        return False
    else:
        return True

#loops through the passed list and removes all %20 words and replaces them with
#the proper spaces.
def FixSpaces(synonyms):

    fixedList = []
    for word in synonyms:
        index = word.find('%20')
        if index == -1:
            fixedList.append(word)
        else:
            newWord = ''
            while index != -1:
                newWord += word[:index] + ' '
                word = word[index+3:]
                index = word.find('%20')
            newWord += word
            fixedList.append(newWord)

    return fixedList

    
    
if __name__ == "__main__":
    keyword = 'move'
    pos = 'verb'
    Syns(keyword,pos)

    
