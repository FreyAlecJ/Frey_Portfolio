#creates two versions of our functions. one that outputs to a file and one
#that returns the object directly

import sys
import os
import time
sys.path.append('..')
from Thesaurus import scraper
import nltk
from nltk.corpus import wordnet

FILEPATH = 'chessCommands.txt'


#This function is passed our keywords and it searches all hyponyms associated
#with those words. Returns the results in a dictionary
#Time = 1.27
def FindHyponymsObject(commands):

    exhaustive = {} #of format {keyword:hyponyms}
    for item in commands:
        syns = wordnet.synsets(item)
        hypos=[]
        for word in syns:
            hyponyms = word.hyponyms()
            for hyp in hyponyms:
                synonyms = hyp.hypernyms()
                for syn in synonyms:
                    word = str(syn.name())
                    word = word.split('.')
                    word = word[0]
                    if word not in hypos:
                        hypos.append(word)
                    
        exhaustive[item] = hypos

    return exhaustive
        
#This function is passed our keywords and it searches all the hyponyms
#associated with them and stores them in a textfile.
#Time = 0.03 s
def FindHyponymsFile(commands):

    exhaustive = {} #of format {keyword:hyponyms}
    for item in commands:
        name = item.replace(' ', '_')
        filename = os.path.join('hypo',name+'.txt')
        myOut = open(filename, 'w')
        syns = wordnet.synsets(item)
        hypos = []
        for word in syns:
            hyponyms = word.hyponyms()
            for hyp in hyponyms:
                synonyms = hyp.hypernyms()
                for syn in synonyms:
                    word = str(syn.name())
                    word = word.split('.')
                    word = word[0]
                    if word not in hypos:
                        word = word.replace('_',' ')
                        hypos.append(word)
                        myOut.write(word + '\n')
        myOut.close()

    return

#This function is passed a keyword to search for. It will perform a fusion
#approach of forward and backward to search more synonyms.
def FusionObject(keyword, pos, exhaustives):
    syns = scraper.Syns(keyword, pos)
    syns.extend(scraper.SynsOfSyns(keyword,pos))

    matches = []
    #check if the keyword is already a command
    if keyword in exhaustives:
        matches.append(keyword)


    #loops through all the generated synonyms to chck if they match
    for syn in syns:
        if syn in exhaustives:
            matches.append(syn)
            continue
        for key in exhaustives:
            if syn in exhaustives[key] and not key in matches:
                matches.append(key)

    return matches
    

#This function is passed our keywords and it seraches all the hypernms
#associated with those words and returns them in a dictionary.
#Time = 0.02s
def FindHypernymsObject(commands):

    exhaustive = {} #of format {keyword:hyponyms}
    for item in commands:
        syns = wordnet.synsets(item)
        visited = []
        hypers=[]
        for word in syns:
            hypernyms = word.hypernyms()
            for hyp in hypernyms:
                synonyms = hyp.hyponyms()
                for syn in synonyms:
                    word = str(syn.name())
                    word = word.split('.')
                    word = word[0]
                    if word not in hypers:
                        hypers.append(word)
        exhaustive[item] = hypers

    return exhaustive

#This function is passed our keywords and it seraches all the hypernms
#associated with those words and stores them in a file
#Time = 1.62
def FindHypernymsFile(commands):


    for item in commands:
        name = item.replace(' ', '_')
        filename = os.path.join('hyper',name+'.txt')
        myOut = open(filename, 'w')
        syns = wordnet.synsets(item)
        visited = []
        for word in syns:
            hypernyms = word.hypernyms()
            for hyp in hypernyms:
                synonyms = hyp.hyponyms()
                for syn in synonyms:
                    word = str(syn.name())
                    word = word.split('.')
                    word = word[0]
                    if word not in visited:
                        word = word.replace('_',' ')
                        visited.append(word)
                        myOut.write(word + '\n')
        myOut.close()

    return
                     
#This function creates a large list of synonyms for each word and
#returns a dictionary in the format of {keyword:synonyms} for use
#in searching for matches.
#Time = 41.09
def CreateExhaustivesObject(commands):
    #builds an exhaustive list of synonyms for each keyword
    exhaustive = {}
    for order in commands:
        syns = scraper.Syns(order, commands[order])
        syns.extend(scraper.SynsOfSyns(order,commands[order]))
        exhaustive[order] = syns

    return exhaustive

#This function creates a large list of synonyms for each word and
#creates a file named "keyword".txt which holds syonyms for use
#in searching for matches.
#Time = 37.56
def CreateExhaustivesFile(commands):
    
    #builds an exhaustive list of synonyms for each keyword
    for order in commands:
        fileOrder = order.replace(' ', '_')
        filename = os.path.join('.',commands[order],fileOrder+'.txt')
        myOut = open(filename, 'w')
        syns = scraper.Syns(order, commands[order])
        syns.extend(scraper.SynsOfSyns(order, commands[order]))
        for item in syns:
            myOut.write(item + '\n')
        myOut.close()

    return
    

#This function searches the exhaustive words precompiles at start
#for the keyword and returns a list of matches.
#Time = 0.00
def ForwardObject(exhaustive,keyword, commands):

    #searches each keyword list for the inpput
    matches = []
    if keyword in commands:
        matches.append(keyword)
    for key in exhaustive:
        if keyword in exhaustive[key]:
            matches.append(key)       
    
    return matches


#This function searches the exhaustive words precompiled at the start
#for the keyword and writes the matches to a file.
#Time = 0.00
def ForwardFile(exhaustive,keyword, commands):

    name = keyword.replace(' ', '_')
    filename = os.path.join('forward', name+'.txt')
    myOut = open(filename, 'w')
    
    #searches each keyword list for the inpput
    if keyword in commands:
        myOut.write(keyword + '\n')
    for key in exhaustive:
        if keyword in exhaustive[key]:
            myOut.write(key + '\n')     
    
    myOut.close()

    return

#This function expands the synonyms for the passed keyword and then
#notes every time a match is found for the commands. Returns a list
#Time = 1.11s
def BackwardObject(keyword, pos, commands):
    
    syns = scraper.Syns(keyword, pos)
    syns.extend(scraper.SynsOfSyns(keyword,pos))

    matches = []
    for order in commands:
        if order == keyword:
            matches.append(order)
        if order in syns:
            matches.append(order)

    return matches

#This function recieves a keyword, pos and the list of commands.
#Then it searches the keywords synonyms for matches on the commands
#list and returns a file containing the matches
#Time = 1.15s
def BackwardFile(keyword, pos, commands):
    
    syns = scraper.Syns(keyword, pos)
    syns.extend(scraper.SynsOfSyns(keyword,pos))

    name = keyword.replace(' ', '_')
    filename = os.path.join('backward', name  + '.txt')
    myOut = open(filename, 'w')

    matches = []
    for order in commands:
        if order == keyword:
            myOut.write(order + '\n')
        if order in syns:
            myOut.write(order + '\n')

    myOut.close()

    return


#This function reads our command file and puts them into a list.
#this needs to be modified later to include the POS from the file.
def ReadCommands(FILEPATH):

    commands = {}
    with open(FILEPATH,'r') as myIn:
        for line in myIn:
            values = line.split(',')
            word = values[0]
            pos = values[1].strip()
            commands[word] = pos
    return commands


#This function will take a filename and read the file. After reading
#the dat will be put into a list and returned for use later.
#time = 0.00
def FileToList(filename):

    inputList = []
    with open(filename, 'r') as myIn:
         for line in myIn:
             inputList.append(line.rstrip())

    return inputList
    
#This function will take a filename and read the file. After reading,
#the data will be put into a dictionary for entry into algorithms
#later.
#to use this file. call the file name, which will return a dictionary
#then use the update method to append the two.
#Ex: dict1 = FiletoDictionary, dict2 = FileTOdictionary, dict1.update(dict2)
#time = 0.00
def FileToDictionary(filename):
    key = filename.split(os.sep)[2].split('.')[0]

    newDictionary = {}
    values = []
    with open(filename, 'r') as myIn:
        for line in myIn:
            values.append(line.rstrip())

    newDictionary[key] = values

    return newDictionary
            

    

    


    




if __name__ == "__main__":
    commands = ReadCommands(FILEPATH)

    exhaustives = CreateExhaustivesObject(commands)
    keepgoing = 'y'
    while keepgoing == 'y':
        keyword = input("Please enter a keyword: ")
        pos = input("Please enter the part of speech: ")
        
        time1 = time.time()
        matches = FusionObject(keyword, pos, exhaustives)
        time2 = time.time()
        print(time2-time1)
        print(matches)
        keepgoing = input("y/n")
    

    

