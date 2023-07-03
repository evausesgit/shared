import requests

from datetime import datetime

headers = {
    'Content-Type': 'application/x-www-form-urlencoded; charset=UTF-8',
    'Accept': 'application/json, text/javascript, */*; q=0.01',
    'Sec-Fetch-Site': 'same-site',
    'Accept-Language': 'en-GB,en;q=0.9',
    # 'Accept-Encoding': 'gzip, deflate, br',
    'Sec-Fetch-Mode': 'cors',
    'Host': 'api.rtrt.me',
    'Origin': 'https://app.rtrt.me',
    'User-Agent':
    'Mozilla/5.0 (Macintosh; Intel Mac OS X 10_15_7) AppleWebKit/605.1.15 (KHTML, like Gecko) Version/16.5 Safari/605.1.15',
    'Referer': 'https://app.rtrt.me/',
    # 'Content-Length': '147',
    'Connection': 'keep-alive',
    'Sec-Fetch-Dest': 'empty',
}

data = {
    'appid': '5824c5c948fd08c23a8b4567',
    'token': 'A0C0CB5DFD1462A45EA5',
    'max': '2000',
    'loc': '1',
    'cbust': '0.40053277598132475',
    'places': '2',
    'etimes': '1',
    'units': 'metric',
    'source': 'webtracker',
}


def query():
    response = requests.post(
        'https://api.rtrt.me/events/IRM-LESSABLESDOLONNE703-2023/profiles/RVBM2GJY/splits',
        headers=headers,
        data=data,
    )
    """

    """

    return response.json()


import os
import time
from tabulate import tabulate

# Known distances for each activity
distances = {
    "START": "0 km",
    "SWIM": "1.9 km",  # For a typical Ironman 70.3 event
    "T1": "Transition 1",
    "BIKE1": "17.0 km",
    "BIKE2": "42.0 km",
    "BIKE3": "72.0 km",
    "BIKE": "90.0 km",
    "T2": "Transition 2",
    "RUN1": "2.5 km",
    "RUN2": "6.8 km",
    "RUN3": "11.7 km",
    "RUN4": "16.0 km",
    "RUN5": "20.9 km",
    "FINISH": "CONGRAT!"
    # Add other labels as needed
}


def fetch_data():
    # Your function to fetch data from the API
    return query()


def print_athlete_info(response):
    # Get general info
    athlete_name = response["list"][0]["name"]
    athlete_sex = response["list"][0]["sex"]
    athlete_country = response["list"][0]["country"]
    athlete_city = response["list"][0]["city"]
    athlete_team = response["list"][0]["team"]
    athlete_division = response["list"][0]["division"]

    # Print general info
    print(
        f"Athlete: {athlete_name}, Sex: {athlete_sex}, Country: {athlete_country}"
    )

    # Get splits info
    splits_data = []
    for item in response["list"]:
        point = item["point"]
        time = item["time"]
        if "pace" in item:
            pace = item["pace"]
        else:
            pace = "N/A"

        if point in distances:
            distance = distances[point]
        else:
            distance = "N/A"

        if 'legTime' in item:
            split_time = item['legTime']
        else:
            split_time = "N/A"

        splits_data.append([point, time, pace, distance, split_time])

    # Print splits info
    print(
        tabulate(splits_data,
                 headers=["Point", "Time", "Pace", "Distance", "Split Time"]))


while True:
    # Fetch the data
    typical_response = fetch_data()

    # Clear the terminal
    os.system('cls' if os.name == 'nt' else 'clear')

    # Print the athlete's information
    print(datetime.now().strftime("%Y-%m-%d %H:%M:%S"))
    print_athlete_info(typical_response)

    # Wait for 15 seconds before fetching the data again
    time.sleep(15)

typical_response = {
    "list": [{
        "time": "00:00:00.00",
        "point": "START",
        "label": "START",
        "pid": "RVBM2GJY",
        "bib": "786",
        "bib_display": "786",
        "tag": "NT74476",
        "name": "Eva Attal",
        "timeOfDay": "10:50:22 am",
        "epochTime": "1688287821.747",
        "startTime": "10:50:22 am",
        "sex": "F",
        "alias": "SWIM START",
        "isStart": "1",
        "course": "ironman703",
        "country": "FRA",
        "country_iso": "fr",
        "city": "Paris",
        "team": "Stade Français",
        "division": "F40-44",
        "timestamp": "1688295021.747",
        "i": "1688287832_000066",
        "u": "1688287832_000067"
    }, {
        "time": "00:42:36.43",
        "point": "SWIM",
        "label": "Swim",
        "pid": "RVBM2GJY",
        "bib": "786",
        "bib_display": "786",
        "tag": "NT74476",
        "name": "Eva Attal",
        "timeOfDay": "11:32:59 am",
        "epochTime": "1688290378.177",
        "milePace": "36:06",
        "milePaceAvg": "36:06",
        "mph": "1.66",
        "kmPace": "22:26",
        "kmPaceAvg": "22:26",
        "kmh": "2.68",
        "etfp": "FINISH~07:44:19~6:34 pm",
        "startTime": "10:50:22 am",
        "sex": "F",
        "alias": "SWIM FINISH",
        "pace": "02:15 min/100m",
        "paceAvg": "02:15 min/100m",
        "legTime": "00:42:36.43",
        "splitTime": "00:42:36.43",
        "netTime": "00:42:36.43",
        "waveTime": "01:23:44.226",
        "course": "ironman703",
        "country": "FRA",
        "country_iso": "fr",
        "city": "Paris",
        "team": "Stade Français",
        "division": "F40-44",
        "timestamp": "1688297578.177",
        "i": "1688290381_000030",
        "u": "1688290381_000031"
    }, {
        "time": "00:59:46.102",
        "point": "T1",
        "label": "T1",
        "pid": "RVBM2GJY",
        "bib": "786",
        "bib_display": "786",
        "tag": "NT74476",
        "name": "Eva Attal",
        "timeOfDay": "11:50:08 am",
        "epochTime": "1688291407.849",
        "milePace": "18:34",
        "milePaceAvg": "18:34",
        "kmPace": "22:07",
        "kmPaceAvg": "22:07",
        "etnp": "BIKE1~01:46:51~12:37 pm",
        "etfp": "FINISH~07:52:31~6:42 pm",
        "startTime": "10:50:22 am",
        "sex": "F",
        "alias": "BIKE START_FINISH",
        "pace": "22:07 min/km",
        "paceAvg": "22:07 min/km",
        "legTime": "00:17:09.672",
        "splitTime": "00:17:09.672",
        "netTime": "00:59:46.102",
        "waveTime": "01:40:53.898",
        "course": "ironman703",
        "country": "FRA",
        "country_iso": "fr",
        "city": "Paris",
        "team": "Stade Français",
        "division": "F40-44",
        "timestamp": "1688298607.849",
        "i": "1688291410_000265",
        "u": "1688291410_000266"
    }, {
        "time": "01:42:08.789",
        "point": "BIKE1",
        "label": "Bike 17.0km",
        "pid": "RVBM2GJY",
        "bib": "786",
        "bib_display": "786",
        "tag": "NT74476",
        "name": "Eva Attal",
        "timeOfDay": "12:32:31 pm",
        "epochTime": "1688293950.536",
        "milePace": "04:01",
        "milePaceAvg": "04:01",
        "mph": "14.96",
        "kmPace": "02:30",
        "kmPaceAvg": "02:30",
        "kmh": "24.07",
        "etnp": "BIKE2~02:44:29~1:34 pm",
        "etfp": "FINISH~07:11:25~6:01 pm",
        "startTime": "10:50:22 am",
        "sex": "F",
        "alias": "BIKE SPLIT 1",
        "pace": "24.07 km/hr",
        "paceAvg": "24.07 km/hr",
        "legTime": "00:42:22.687",
        "splitTime": "00:42:22.687",
        "netTime": "01:42:08.789",
        "waveTime": "02:23:16.585",
        "course": "ironman703",
        "country": "FRA",
        "country_iso": "fr",
        "city": "Paris",
        "team": "Stade Français",
        "division": "F40-44",
        "timestamp": "1688301150.536",
        "i": "1688293952_000146",
        "u": "1688293952_000147"
    }],
    "info": {
        "first": "1",
        "last": "4",
        "cacheVer": "0~0",
        "loc": {
            "RVBM2GJY": {
                "multiplier": "1",
                "last": {
                    "ts": 1688293950,
                    "sts": 1688287821,
                    "npm": 27.5267,
                    "npn": "BIKE2",
                    "lpm": 11.9924,
                    "lpn": "BIKE1",
                    "lppn": "BIKE1",
                    "fpn": "FINISH",
                    "fpm": 71.7683,
                    "mps": 240.71,
                    "amps": 511.06
                },
                "pace": "24.07 km/hr",
                "paceAvg": "11.34 km/hr",
                "etimecoords": "1",
                "transec": "1029.672",
                "etimes": {
                    "BIKE2": {
                        "label": "Bike 42.0km",
                        "time": "01:44:43",
                        "timeOfDay": "1:34 pm",
                        "epochTime": "1688297690.00",
                        "coords": {
                            "lat": 46.568629,
                            "lng": -1.516491
                        }
                    },
                    "BIKE3": {
                        "label": "BIKE 72.0km",
                        "time": "02:59:30",
                        "timeOfDay": "2:49 pm",
                        "epochTime": "1688302177.00",
                        "coords": {
                            "lat": 46.601706,
                            "lng": -1.752222
                        }
                    },
                    "BIKE": {
                        "label": "Bike",
                        "time": "03:49:06",
                        "timeOfDay": "3:39 pm",
                        "epochTime": "1688305153.00",
                        "coords": {
                            "lat": 46.503845,
                            "lng": -1.788517
                        }
                    }
                },
                "epc": "19.275",
                "emiles": "13.834",
                "legemiles": "12.405",
                "mph": "14.96",
                "sslp": "941",
                "sss": "7070",
                "lpn": "BIKE1",
                "lppn": "BIKE1",
                "npn": "BIKE2",
                "course": "ironman703",
                "wavestart": "1688285353.951"
            }
        },
        "places": {
            "RVBM2GJY": {
                "leg": {
                    "SWIM": {
                        "course-sex-division": {
                            "p": "58",
                            "n": "F40-44",
                            "t": "58",
                            "path": "/places/course-sex-division/SWIM",
                            "combo": {
                                "course": "ironman703",
                                "sex": "F",
                                "division": "F40-44"
                            }
                        },
                        "course-sex": {
                            "p": "357",
                            "n": "by Gender",
                            "t": "357",
                            "path": "/places/course-sex/SWIM",
                            "combo": {
                                "course": "ironman703",
                                "sex": "F"
                            }
                        },
                        "course": {
                            "p": "2689",
                            "n": "Overall",
                            "t": "2689",
                            "path": "/places/course/SWIM",
                            "combo": {
                                "course": "ironman703"
                            }
                        }
                    }
                }
            }
        }
    }
}
