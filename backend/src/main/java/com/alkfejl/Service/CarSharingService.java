package com.alkfejl.Service;

import com.alkfejl.Entity.Car;
import com.alkfejl.Entity.User;
import com.alkfejl.Repository.CarRepository;
import com.alkfejl.Repository.UserRepository;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;

import javax.mail.*;
import javax.mail.internet.*;
import java.io.IOException;
import java.util.Date;
import java.util.List;
import java.util.Properties;


@Service
public class CarSharingService {
    @Autowired
    private CarRepository carRepository;

    @Autowired
    private UserRepository userRepository;

    public void addCar(Car car){ this.carRepository.save(car); };

    public Iterable<Car> getAllCars() { return this.carRepository.findAll(); }

    public void addUser(User user) { this.userRepository.save(user); }

    public String signIn(User user) {
        List<User> users = userRepository.findAll();
        for(User u : users){
            if(u.getName().equals(user.getName()))
                if(u.getPassword().equals(user.getPassword()))
                    return u.getRole();
        }
        return "";
    }

    public Iterable<Car> getCarByOwner(String owner) {
        List<Car> cars = carRepository.findAll();
        for(Car c: cars){
            if(c.getOwner().equals(owner))
                cars.remove(c);
        }
        return cars;
    }

    public String sendEmail(Car car) throws AddressException, MessagingException, IOException {
        Properties props = new Properties();
        props.put("mail.smtp.auth", "true");
        props.put("mail.smtp.starttls.enable", "true");
        props.put("mail.smtp.host", "smtp.gmail.com");
        props.put("mail.smtp.port", "587");

        Session session = Session.getInstance(props, new javax.mail.Authenticator() {
            protected PasswordAuthentication getPasswordAuthentication() {
                return new PasswordAuthentication("c4rsh4ring@gmail.com", "jelszojelszo");
            }
        });
        Message msg = new MimeMessage(session);
        msg.setFrom(new InternetAddress("c4rsh4ring@gmail.com", false));

        String owner = "";
        List<Car> cars = carRepository.findAll();
        for(Car c: cars){
            if(c.getLicensePlate().equals(car.getLicensePlate()))
                owner = c.getOwner();
        }
        String email = "";
        if(!owner.isEmpty()){
            List<User> users = userRepository.findAll();
            for(User u : users){
                if(u.getName().equals(owner))
                    email = u.getEmail();
            }
        }

        msg.setRecipients(Message.RecipientType.TO, InternetAddress.parse(email));
        msg.setSubject("Car Sharing");
        msg.setContent("CarSharing", "text/html");
        msg.setSentDate(new Date());

        MimeBodyPart messageBodyPart = new MimeBodyPart();
        messageBodyPart.setContent("Az autódat lefoglalták.", "text/html");

        Multipart multipart = new MimeMultipart();
        multipart.addBodyPart(messageBodyPart);
        msg.setContent(multipart);
        Transport.send(msg);

        return "Renting successful";
    }
}
