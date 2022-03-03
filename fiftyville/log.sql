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
SELECT * FROM phone_calls WHERE year = "2021" and month  = "7" and day = "28" and duration <= 40;