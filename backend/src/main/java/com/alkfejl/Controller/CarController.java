package com.alkfejl.Controller;

import com.alkfejl.Entity.Car;
import com.alkfejl.Service.CarSharingService;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.http.MediaType;
import org.springframework.web.bind.annotation.*;

@RestController
@RequestMapping("/cars")
public class CarController {

    @Autowired
    private CarSharingService carSharingService;

    @RequestMapping(method = RequestMethod.POST, consumes = MediaType.APPLICATION_JSON_VALUE)
    public void addCar(@RequestBody Car c) {carSharingService.addCar(c);}

    @RequestMapping(method = RequestMethod.GET)
    public Iterable<Car> getAllCars(){return this.carSharingService.getAllCars();}

    @RequestMapping(value = "/{owner}", method = RequestMethod.GET)
    public Iterable<Car> getCarByOwner(@PathVariable("owner") String owner){
        return carSharingService.getCarByOwner(owner);
    }
}
