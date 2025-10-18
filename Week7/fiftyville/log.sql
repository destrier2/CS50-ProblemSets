-- Keep a log of any SQL queries you execute as you solve the mystery.

/*
Find anything on July 28, 2024 that took place on Humphrey Street. This gives us a good starting point
ID found! The id of the crime is 295, took place at 10:15am at a bakery. 
Witness interviews took place on the same day, and ther interview transcripts say "bakery"
*/
SELECT * FROM crime_scene_reports WHERE year = 2024 AND month = 7 AND day = 28 AND street = 'Humphrey Street';

/*
Search the witness interviews for anything that took place on the same day and say "bakery". 
The three ids: 161, 162, 163
161: Look for security footage from the bakery parking lot for cars leaving within 10 minutes of 10:15
162: The bakery is owned by someone named "Emma", and the thief withdrew money from an ATM on Leggett 
    Street on the same day
163: Check flight logs --> all flights for tomorrow (29th). Check phone calls --> under a minute.
    The person who got called is the person who bought the ticket (accomplice).

*/
SELECT * from interviews WHERE year = 2024 AND month = 7 AND day = 28 AND transcript LIKE ('%bakery%');

/*
EXTRA
Check for phone calls on the same day, just to see if we're lucky and maybe there's only one or two
Unfortunately not :( Ok, time to go cross reference people, phone calls, and atm records
*/
SELECT * FROM phone_calls WHERE year = 2024 AND month = 7 AND day = 28 AND duration < 60;

/*
Print everyone who accessed the atm that morning and also called within for under a minute on the same day. 
This helps limit the list of suspects to five people: Kenny, Benista, Taylor, Diana, and Bruce. 
Next, I should also look for the car license plate
*/
SELECT * FROM people WHERE id IN (
    SELECT person_id FROM atm_transactions JOIN bank_accounts ON atm_transactions.account_number = bank_accounts.account_number WHERE year = 2024 AND month = 7 AND day = 28 and atm_location = 'Leggett Street'
) AND phone_number IN (
    SELECT caller FROM phone_calls WHERE year = 2024 AND month = 7 AND day = 28 AND duration < 60
    UNION
    SELECT receiver FROM phone_calls WHERE year = 2024 AND month = 7 AND day = 28 AND duration < 60
);

/*
Print all the cars that left within that the time frame of the burglary. 
No luck! There are multiple cars that left within that time. Time to compare this with the above results.
*/
SELECT * FROM bakery_security_logs WHERE year = 2024 AND month = 7 AND day = 28 AND hour = 10 AND activity = 'exit' AND minute <= 25 AND minute >= 15;

/*
Compare the list of people who called within that time frame, accessed the atm on the same day, and their car liscense plates
This gave me two results! Diana and Bruce. Suspect list successfully narrowed!
*/
SELECT * FROM people WHERE license_plate IN (
    SELECT bakery_security_logs.license_plate FROM bakery_security_logs WHERE year = 2024 AND month = 7 AND day = 28 AND hour = 10 AND activity = 'exit' AND minute <= 25 AND minute >= 15
) AND id IN (
    SELECT person_id FROM atm_transactions JOIN bank_accounts ON atm_transactions.account_number = bank_accounts.account_number WHERE year = 2024 AND month = 7 AND day = 28 and atm_location = 'Leggett Street'
) AND phone_number IN (
    SELECT caller FROM phone_calls WHERE year = 2024 AND month = 7 AND day = 28 AND duration < 60
    UNION
    SELECT receiver FROM phone_calls WHERE year = 2024 AND month = 7 AND day = 28 AND duration < 60
);

/*
Print out all the airports, just to get a sense of the possibilities and try to find the local airport. 
Success! The local airport has an id of 8 and is Fiftyville Regional Airport. 
*/
SELECT * FROM airports;

/*
Next, check all passengers on flights leaving tomorrow for the passport for either Diana or Bruce
Diana bought two tickets! Extra suspicious. Perhaps she is the accomplice? 
*/
SELECT * FROM people JOIN passengers ON passengers.passport_number = people.passport_number WHERE passengers.flight_id IN (
    SELECT flights.id FROM flights JOIN airports ON airports.id = flights.origin_airport_id WHERE airports.abbreviation = 'CSF'
) AND  license_plate IN (
    SELECT bakery_security_logs.license_plate FROM bakery_security_logs WHERE year = 2024 AND month = 7 AND day = 28 AND hour = 10 AND activity = 'exit' AND minute <= 25 AND minute >= 15
) AND id IN (
    SELECT person_id FROM atm_transactions JOIN bank_accounts ON atm_transactions.account_number = bank_accounts.account_number WHERE year = 2024 AND month = 7 AND day = 28 and atm_location = 'Leggett Street'
) AND phone_number IN (
    SELECT caller FROM phone_calls WHERE year = 2024 AND month = 7 AND day = 28 AND duration < 60
    UNION
    SELECT receiver FROM phone_calls WHERE year = 2024 AND month = 7 AND day = 28 AND duration < 60
);

/*
Let's take a closer look at the flights. It seems like the earliest flight is the one with the id 36, which is the one Bruce is one!
Bruce must be the thief! He is heading to airport 4, which is LaGuardia Airport in New York City!
*/
SELECT * FROM flights WHERE year = 2024 AND month = 7 AND day = 29 AND origin_airport_id = 8;

/*
Time to go back to the calls and see who Bruce called! 
Looks like the phone number he called was (375) 555-8161
*/
SELECT people.name, people.phone_number, people.passport_number, people.license_plate, caller, receiver, duration FROM people JOIN phone_calls ON people.phone_number = phone_calls.caller WHERE people.name = 'Bruce' AND year = 2024 AND month = 7 AND day = 28 AND duration < 60;

/*
Almost there! Print out the person who he called. 
He called "Robin" --> that must be the accomplice
*/
SELECT * FROM people WHERE phone_number = '(375) 555-8161';


