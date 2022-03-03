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
SELECT * FROM phone_calls WHERE year = "2021" and month  = "7" and day = "28" and duration <= 45;

--airports
-- origin_flight_id = 8
SELECT * FROM airports;

--flights
--flight from Fiftyville and in the morning
--destination_airport_id = 4 or 1
SELECT * FROM flights WHERE year = "2021" and month = "7" and day = "29" and origin_airport_id = 8 and hour < 12;
-- +----+-------------------+------------------------+------+-------+-----+------+--------+
-- | id | origin_airport_id | destination_airport_id | year | month | day | hour | minute |
-- +----+-------------------+------------------------+------+-------+-----+------+--------+
-- | 36 | 8                 | 4                      | 2021 | 7     | 29  | 8    | 20     |
-- | 43 | 8                 | 1                      | 2021 | 7     | 29  | 9    | 30     |
-- +----+-------------------+------------------------+------+-------+-----+------+--------+

--get tel no. caller : (031) 555-6622, receiver: (910) 555-3251
SELECT * FROM phone_calls WHERE year = "2021" and month  = "7" and day = "28" and duration = 38;

--people, query by phone number
SELECT * FROM people WHERE phone_number IN (SELECT caller FROM phone_calls WHERE year = "2021" and month  = "7" and day = "28" and duration = 38);
SELECT * FROM people WHERE phone_number IN (SELECT receiver FROM phone_calls WHERE year = "2021" and month  = "7" and day = "28" and duration = 38);
-- id   |  name  |  phone_number  | passport_number | license_plate
-- 907148 | Carina | (031) 555-6622 | 9628244268      | Q12B3Z3

--receiver:
--712712 | Jacqueline | (910) 555-3251 |                 | 43V0R5D

-- find the transactions with bank account number to get the person_id
SELECT person_id FROM bank_accounts WHERE account_number IN (SELECT account_number FROM atm_transactions WHERE year = "2021" and month  = "7" and day = "28" and transaction_type = "withdraw" and atm_location = "Leggett Street");
--  686048    |
-- | 514354    |
-- | 458378    |
-- | 395717    |
-- | 396669    |
-- | 467400    |
-- | 449774    |
-- | 438727
SELECT * FROM people WHERE phone_number IN (SELECT caller FROM phone_calls WHERE year = "2021" and month  = "7" and day = "28" and duration >=20 and duration <= 45);
SELECT * FROM people WHERE phone_number IN (SELECT receiver FROM phone_calls WHERE year = "2021" and month  = "7" and day = "28" and duration >=20 and duration <= 45);
-- |   id   |  name  |  phone_number  | passport_number | license_plate |
--  449774 | Taylor | (286) 555-6063 | 1988161715      | 1106N58       | <<<
-- | 560886 | Kelsey | (499) 555-9472 | 8294398571      | 0NTHK55       |
-- | 686048 | Bruce  | (367) 555-5533 | 5773159633      | 94KL13X       |<<<
-- | 907148 | Carina | (031) 555-6622 | 9628244268      | Q12B3Z3       |

--Taylor and Bruce match the caller table and atm withdrawal table

--receiver
-- +--------+------------+----------------+-----------------+---------------+
-- |   id   |    name    |  phone_number  | passport_number | license_plate |
-- +--------+------------+----------------+-----------------+---------------+
-- | 250277 | James      | (676) 555-6554 | 2438825627      | Q13SVG6       |
-- | 251693 | Larry      | (892) 555-8872 | 2312901747      | O268ZZ0       |
-- | 712712 | Jacqueline | (910) 555-3251 |                 | 43V0R5D       |
-- | 864400 | Robin      | (375) 555-8161 |                 | 4V16VO0       |

--passengers
SELECT * FROM passengers WHERE passport_number = "1988161715" or passport_number="5773159633";
+-----------+-----------------+------+
| flight_id | passport_number | seat |
+-----------+-----------------+------+
| 36        | 5773159633      | 4A   |
| 36        | 1988161715      | 6D   |
+-----------+-----------------+------+

--passengers who take the flight of flight_id = 36
SELECT * FROM passengers WHERE flight_id = 36;
+-----------+-----------------+------+
| flight_id | passport_number | seat |
+-----------+-----------------+------+
| 36        | 7214083635      | 2A   |
| 36        | 1695452385      | 3B   |
| 36        | 5773159633      | 4A   |
| 36        | 1540955065      | 5C   |
| 36        | 8294398571      | 6C   |
| 36        | 1988161715      | 6D   |
| 36        | 9878712108      | 7A   |
| 36        | 8496433585      | 7B   |
+-----------+-----------------+------+