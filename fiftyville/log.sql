-- Keep a log of any SQL queries you execute as you solve the mystery.

--bakery_security_logs
--To get the data of hour and minute that the thief entered at
SELECT * FROM bakery_security_logs WHERE month = "7" and day = "28";

--crime_scene_reports
--To get the time for duck took place in 10:15 am
SELECT * FROM crime_scene_reports WHERE year = "2021" and month = "7" and day = "28" and street = "Humphrey Street";

--interviews
-- within 10mins of theft, security parking lot
-- Leggett Street, thief ,ATM, withdraw money before 10:15am
-- earliest flight tomorrow 1 min call after 10:15am
-- someone came in for half an hour, in a phone call for 30mins
-- EMMA's bakery
SELECT * FROM interviews WHERE year = "2021" and month = "7" and day= "28";

--ATM transactions
-- get all transactions with the date, transaction_type and atm_location
SELECT * FROM atm_transactions WHERE year = "2021" and month  = "7" and day = "28" and transaction_type = "withdraw" and atm_location = "Leggett Street";

--phone calls
-- duration is 38mins which would match the entrance and exit record
SELECT * FROM phone_calls WHERE year = "2021" and month  = "7" and day = "28" and duration <= 40;

--airports
-- origin_flight_id = 8
SELECT * FROM airports;

--flights
--flight from Fiftyville and in the morning
--destination_airport_id = 4 or 1
SELECT * FROM flights WHERE year = "2021" and month = "7" and day = "29" and origin_airport_id = 8 and hour < 12;

--get tel no. caller : (031) 555-6622, receiver: (910) 555-3251
SELECT * FROM phone_calls WHERE year = "2021" and month  = "7" and day = "28" and duration = 38;

