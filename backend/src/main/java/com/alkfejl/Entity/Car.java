package com.alkfejl.Entity;

import javax.persistence.Entity;
import javax.persistence.Id;

@Entity
public class Car {

    @Id
    private String licensePlate;
    private String owner;
    private String name;

    public Car(String licensePlate, String owner, String name) {
        this.licensePlate = licensePlate;
        this.owner = owner;
        this.name = name;
    }

    public Car(){};

    public String getLicensePlate() {
        return licensePlate;
    }

    public void setLicensePlate(String licensePlate) {
        this.licensePlate = licensePlate;
    }

    public String getOwner() {
        return owner;
    }

    public void setOwner(String owner) {
        this.owner = owner;
    }

    public String getName() {
        return name;
    }

    public void setName(String name) {
        this.name = name;
    }
}
