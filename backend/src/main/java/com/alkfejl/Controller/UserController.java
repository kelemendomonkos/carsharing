package com.alkfejl.Controller;

import com.alkfejl.Entity.Car;
import com.alkfejl.Entity.User;
import com.alkfejl.Service.CarSharingService;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.http.MediaType;
import org.springframework.web.bind.annotation.RequestBody;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RequestMethod;
import org.springframework.web.bind.annotation.RestController;

import javax.mail.MessagingException;
import java.io.IOException;

@RestController
@RequestMapping("/users")
public class UserController {

    @Autowired
    private CarSharingService carSharingService;

    @RequestMapping(method = RequestMethod.POST, consumes = MediaType.APPLICATION_JSON_VALUE)
    public void addUser(@RequestBody User user) {carSharingService.addUser(user);}

    @RequestMapping(value = "/login", method = RequestMethod.POST, consumes = MediaType.APPLICATION_JSON_VALUE)
    public String SignIn(@RequestBody User user) {return carSharingService.signIn(user);}

    @RequestMapping(value = "/mail", method = RequestMethod.POST, consumes = MediaType.APPLICATION_JSON_VALUE)
    public String sendEmail(@RequestBody Car car) throws IOException, MessagingException {return carSharingService.sendEmail(car);}
}
