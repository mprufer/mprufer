import sys
import numpy as np

class Date:
    month = None
    day = None
    year = None

    def __init__(self):
        self.month = self.month
        self.day = self.day
        self.year = self.year

    def calMonth(self):
        while True:
            try:
                 month = int(input('Enter a month in digits: '))
            except ValueError:
                print("Please enter a valid input")
                continue
            if (month < 1) or (month > 12):
                continue
            else:
                break

        return month

    def calDay(self, year, month):
        days = [0,31,28,30,31,30,31,30,31,30,31,30,31]

        if (year % 4 == 0 and year % 100 != 0) or year % 400 == 0:
            days[2] = 29

        while True:
            try:
                 day = int(input('Enter a day in digits: '))
            except ValueError:
                print("Please enter a valid input")
                continue
            if day < 0 or day > days[month]:
                print("Please enter a valid input")
                continue
            else:
                break

        return day

    def calYear(self):

        while True:
            try:
                year = int(input('Enter a year in digits: '))
            except ValueError:
                print("Please enter a valid input")
                continue
            if (year < 0):
                continue
            else:
                break

        return year

    def calDate(self):
        year = self.calYear()
        month = self.calMonth()
        day = self.calDay(year, month)


        if month == 1 or month == 2:
            month += 12
            year = year - 1

        exday = (day + np.floor((13 * (month + 1)) / 5) + year % 100 + np.floor(year % 100 / 4) +
                 np.floor(np.floor(year / 100) / 4) - 2 * np.floor(year / 100)) % 7

        if exday == 1:
            print("You were born on a Sunday.")
        elif exday == 2:
            print("You were born on a Monday.")
        elif exday == 3:
            print("You were born on a Tuesday.")
        elif exday == 4:
            print("You were born on a Wednesday.")
        elif exday == 5:
            print("You were born on a Thursday.")
        elif exday == 6:
            print("You were born on a Friday.")
        elif exday == 0:
            print("You were born on a Sunday.")

