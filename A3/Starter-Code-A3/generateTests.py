import random
import sys
def getRandomNumber(l,r):
    return random.randrange(l,r+1)
alphabet=[chr(i) for i in range(ord('a'),ord('z')+1)]
alphabet.extend([chr(i) for i in range(ord('A'),ord('Z')+1)])
alphabet.extend([chr(i) for i in range(ord('0'),ord('9')+1)])
alphabet.extend('_')
"""
 gets a name in of length at least l and atmost r.
"""
def generateNewAccountName(l,r):
    length=getRandomNumber(l,r)
    generatedName=""
    for i in range(length):
        generatedName+=str(alphabet[getRandomNumber(0,len(alphabet)-1)])
    return generatedName

def getRandomNumberWithDist(L):
    sum=0
    for i in L:
        sum+=i
    x=getRandomNumber(1,sum)
    c=1
    partialSum=0
    for i in L:
        partialSum+=i
        if(x<=partialSum):
            return c
        c+=1
#on scale of 1000
probabilityToCreateNewaccount=100
probabilityOfAddTransactionToExistingAccount=200
probabilityOfAddTransactionToNonExistingAccount=100
probabilityOfChekingTopKbalance=10
probabilityOfCheckingBalanceOfAccount=200
probabilityOfDeletingAccountThatNotExist=100
probabilityOfDeletingAccountThatExist=100
probabilityOfCheckingIfAccountExist=100
probabilityOfAskingAccountCount=100

numOperations=int(sys.argv[1])

accNameLengthMin=5
accNameLengthMax=30

#on a scale of 100
probalilityOfAddingPositiveCreditToAccount=50
probabilityOfChekingBalanceOfNonExistingAccount=50
probabilityOfInvolvingAnDeletedAccount=50
probabilityOfCheckingIfExistingAccountExit=50
#generation part
accounts=[]
balances=[]
deletedAccounts=[]
for _ in range(numOperations):
    operatonToDo=getRandomNumberWithDist([probabilityToCreateNewaccount,
                                            probabilityOfAddTransactionToExistingAccount,
                                            probabilityOfAddTransactionToNonExistingAccount,
                                            probabilityOfChekingTopKbalance,
                                            probabilityOfCheckingBalanceOfAccount,
                                            probabilityOfDeletingAccountThatExist,
                                            probabilityOfDeletingAccountThatNotExist,
                                            probabilityOfCheckingIfAccountExist,
                                            probabilityOfAskingAccountCount])
    if(operatonToDo==1):
        accName=generateNewAccountName(accNameLengthMin,accNameLengthMax)
        while(accName in accounts or accName in deletedAccounts):
            accName=generateNewAccountName(accNameLengthMin,accNameLengthMax)
        if(len(deletedAccounts)>0 and getRandomNumber(0,100)<probabilityOfInvolvingAnDeletedAccount):
            accName=deletedAccounts[getRandomNumber(0,len(deletedAccounts)-1)]
            deletedAccounts.remove(accName)
        accBalance=getRandomNumber(0,1000)
        accounts.append(accName)
        balances.append(accBalance)
        print("1",accName,accBalance)
        print(accBalance)
        pass
    elif(operatonToDo==2):
        if(len(accounts)==0):
            continue
        accIndex=getRandomNumber(0,len(accounts)-1)
        accName=accounts[accIndex]
        if(getRandomNumber(0,100)<probalilityOfAddingPositiveCreditToAccount):
            transactionAmount=getRandomNumber(1,1000)
        else:
            transactionAmount=getRandomNumber(-balances[accIndex],0)
        print("2",accName,transactionAmount)
        balances[accIndex]+=transactionAmount
        print(balances[accIndex])
        pass
    elif(operatonToDo==3):
        accName=generateNewAccountName(accNameLengthMin,accNameLengthMax)
        while(accName in accounts or accName in deletedAccounts):
            accName=generateNewAccountName(accNameLengthMin,accNameLengthMax)
        if(len(deletedAccounts)>0 and getRandomNumber(0,100)<probabilityOfInvolvingAnDeletedAccount):
            accName=deletedAccounts[getRandomNumber(0,len(deletedAccounts)-1)]
            deletedAccounts.remove(accName)
        accBalance=getRandomNumber(0,1000)
        accounts.append(accName)
        balances.append(accBalance)
        print("2",accName,accBalance)
        print(accBalance)
        pass
    elif(operatonToDo==4):
        requesingK=getRandomNumber(0,int(len(accounts)*1.5)) # this ensures asking 33% chance of asking length greater than total accounts.
        print(4,requesingK)
        balancesCopy=balances[::]
        balancesCopy.sort(reverse=True)
        print(min(requesingK,len(balancesCopy)),"",end="")
        for i in range(0,min(requesingK,len(balancesCopy))):
            print(balancesCopy[i],"",end="")
        print()
    elif(operatonToDo==5):
        if(getRandomNumber(0,100)<probabilityOfChekingBalanceOfNonExistingAccount):
            if(len(deletedAccounts)>0 and getRandomNumber(0,100)<probabilityOfInvolvingAnDeletedAccount):
                print(5,deletedAccounts[getRandomNumber(0,len(deletedAccounts)-1)])
                print(-1)
                pass
            else:
                accName=generateNewAccountName(accNameLengthMin,accNameLengthMax)
                while(accName in accounts):
                     accName=generateNewAccountName(accNameLengthMin,accNameLengthMax)
                print(5,accName)
                print(-1)
            pass
        else:
            if(len(accounts)==0):
                continue
            accIndex=getRandomNumber(0,len(accounts)-1)
            print(5,accounts[accIndex])
            print(balances[accIndex])
        pass
    elif(operatonToDo==6):
        if(len(accounts)==0):
            continue
        accIndex=getRandomNumber(0,len(accounts)-1)
        print(6,accounts[accIndex])
        print(1)
        deletedAccounts.append(accounts[accIndex])
        accounts.pop(accIndex)
        balances.pop(accIndex)
        pass
    elif(operatonToDo==7):
        if(len(deletedAccounts)>0 and getRandomNumber(0,100)<probabilityOfInvolvingAnDeletedAccount):
            print(6,deletedAccounts[getRandomNumber(0,len(deletedAccounts)-1)])
            print(0)
            pass
        else:
            accName=generateNewAccountName(accNameLengthMin,accNameLengthMax)
            while(accName in accounts):
                accName=generateNewAccountName(accNameLengthMin,accNameLengthMax)
            print(6,accName)
            print(0)
        pass
    elif(operatonToDo==8):
        if(len(accounts)>0 and probabilityOfCheckingIfExistingAccountExit>getRandomNumber(0,100)):
            print(8,accounts[getRandomNumber(0,len(accounts)-1)])
            print(1)
        elif(len(deletedAccounts)>0 and getRandomNumber(0,100)<probabilityOfInvolvingAnDeletedAccount):
            print(8,deletedAccounts[getRandomNumber(0,len(deletedAccounts)-1)])
            print(0)
            pass
        else:
            accName=generateNewAccountName(accNameLengthMin,accNameLengthMax)
            while(accName in accounts):
                accName=generateNewAccountName(accNameLengthMin,accNameLengthMax)
            print(8,accName)
            print(0)
        pass
    elif(operatonToDo==9):
        print(9)
        print(len(accounts))


