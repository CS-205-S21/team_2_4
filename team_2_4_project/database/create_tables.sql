CREATE TABLE Shelter (
  shelter_id INTEGER NOT NULL,
  name TEXT,
  location,
  email
);

CREATE TABLE Pet (
  pet_id, 
  name, 
  location, 
  shelter_id, 
  pet_attribute_id
);

CREATE TABLE Pet_Attributes (
  Pet_Attribute_id, 
  Age,
  Breed, 
  Color, 
  Hair_Length, 
  Weight, 
  Origin, 
  Hypoallergenic, 
  Description
);

CREATE TABLE Adopter (
  adopter_id,
  name,
  email,
  adopter_preferences_id,
  weight,
  origin,
  hypoallergenic
);
