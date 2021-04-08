CREATE TABLE [IF NOT EXISTS] Shelter (
  shelter_id INTEGER UNIQUE NOT NULL PRIMARY KEY,
  name TEXT,
  location TEXT,
  email TEXT
);

CREATE TABLE [IF NOT EXISTS] Pet (
  pet_id INTEGER UNIQUE NOT NULL PRIMARY KEY, 
  name TEXT, 
  location TEXT, 
  shelter_id INTEGER NOT NULL FOREIGN KEY, 
  pet_attribute_id INTEGER NOT NULL FOREIGN KEY
);

CREATE TABLE [IF NOT EXISTS] Pet_Attributes (
  Pet_Attribute_id INTEGER UNIQUE NOT NULL PRIMARY KEY, 
  Age INTEGER,
  Breed TEXT, 
  Color TEXT, 
  Hair_Length TEXT, 
  Weight INTEGER, 
  Origin TEXT, 
  Hypoallergenic TEXT, 
  Description TEXT
);

CREATE TABLE [IF NOT EXISTS] Adopter (
  adopter_id INTEGER UNIQUE NOT NULL PRIMARY KEY,
  name TEXT NOT NULL,
  email TEXT,
  adopter_preferences_id INTEGER FOREIGN KEY,
  weight INTEGER,
  origin TEXT,
  hypoallergenic TEXT
);
