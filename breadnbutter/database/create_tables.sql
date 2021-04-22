CREATE TABLE User (
  user_id INTEGER UNIQUE NOT NULL PRIMARY KEY AUTOINCREMENT,
  name TEXT NOT NULL,
  location TEXT NOT NULL,
  email TEXT NOT NULL,
  password TEXT NOT NULL,
  is_adopter INTEGER NOT NULL
  );

CREATE TABLE Shelter (
  shelter_id INTEGER UNIQUE NOT NULL PRIMARY KEY AUTOINCREMENT, 
  owner_id INTEGER,
  name TEXT, 
  location TEXT, 
  email TEXT,
  FOREIGN KEY(owner_id) REFERENCES User(user_id)
  );

CREATE TABLE Pet (
  pet_id INTEGER UNIQUE NOT NULL PRIMARY KEY AUTOINCREMENT, 
  name TEXT NOT NULL, 
  shelter_id INTEGER NOT NULL,
  pet_attribute_id INTEGER,
  color TEXT,
  hair_length TEXT,
  description TEXT,
  --Image BLOB,
  FOREIGN KEY(pet_attribute_id) REFERENCES Pet_Attributes(Pet_Attribute_id),
  FOREIGN KEY(shelter_id) REFERENCES Shelter(shelter_id)
  );

CREATE TABLE Pet_Attributes ( -- ANYTHING WE WANT TO SEARCH BY
  pet_att_id INTEGER UNIQUE NOT NULL PRIMARY KEY AUTOINCREMENT,
  pet_id INTEGER UNIQUE NOT NULL,
  is_cat INTEGER,
  age INTEGER,
  breed TEXT,
  weight INTEGER,
  origin TEXT,
  hypoallergenic INTEGER,
  FOREIGN KEY(pet_id) REFERENCES Pet(Pet_id)
  );

CREATE TABLE Adopter_Preferences (
  adopter_pref_id INTEGER UNIQUE NOT NULL PRIMARY KEY AUTOINCREMENT,
  adopter_id INTEGER NOT NULL,
  age_min INTEGER,
  age_max INTEGER,
  breed_pref_id INTEGER UNIQUE,
  weight_min INTEGER,
  weight_max INTEGER,
  origin TEXT,
  hypoallergenic INTEGER,
  wants_cat INTEGER,
  FOREIGN KEY(adopter_id) REFERENCES Adopter(user_id)
  );

CREATE TABLE Liked_By (
  liked_by_id INTEGER UNIQUE NOT NULL PRIMARY KEY AUTOINCREMENT,
  adopter_id INTEGER NOT NULL,
  pet_id INTEGER NOT NULL,
  FOREIGN KEY(adopter_id) REFERENCES Adopter(user_id),
  FOREIGN KEY(pet_id) REFERENCES Pet(pet_id)
  );

CREATE TABLE Breed_Pref (
  breed_pref_id INTEGER UNIQUE NOT NULL PRIMARY KEY AUTOINCREMENT,
  breed_id INTEGER NOT NULL,
  adopter_id INTEGER NOT NULL,
  FOREIGN KEY(breed_id) REFERENCES Breeds(breed_id),
  FOREIGN KEY(adopter_id) REFERENCES Adopter(adopter_id)
  );

CREATE TABLE Breeds (
  breed_id INTEGER UNIQUE NOT NULL PRIMARY KEY AUTOINCREMENT,
  breed_name TEXT NOT NULL
  );

