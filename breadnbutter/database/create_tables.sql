CREATE TABLE Shelter (
  shelter_id INTEGER UNIQUE NOT NULL PRIMARY KEY, 
  name TEXT, 
  location TEXT, 
  email TEXT
  );

CREATE TABLE Pet_Attributes (
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

CREATE TABLE Pet (
  pet_id INTEGER UNIQUE NOT NULL PRIMARY KEY, 
  name TEXT, 
  shelter_id INTEGER NOT NULL,
  pet_attribute_id INTEGER,
  --Image BLOB,
  FOREIGN KEY(pet_attribute_id) REFERENCES Pet_Attributes(Pet_Attribute_id),
  FOREIGN KEY(shelter_id) REFERENCES Shelter(shelter_id)
  );

CREATE TABLE Adopter (
  adopter_id INTEGER UNIQUE NOT NULL PRIMARY KEY,
  name TEXT NOT NULL,
  email TEXT NOT NULL,
  password TEXT NOT NULL,
  adopter_preferences_id INTEGER,
  FOREIGN KEY(adopter_preferences_id) REFERENCES Pet_Attributes(Pet_Attribute_id)
  );

--CREATE TABLE LikedBy ();