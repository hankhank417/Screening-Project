import { Component, OnInit } from '@angular/core';
import { NgForm, FormGroup, FormBuilder, FormControl, Validators } from '@angular/forms';
import { Router } from '@angular/router';

import { MenuController } from '@ionic/angular';

import { UserData } from '../../providers/user-data';
import { UserOptions } from '../../interfaces/user-options';
import { AuthService } from '../../auth.service';



@Component({
  selector: 'page-login',
  templateUrl: 'login.html',
  styleUrls: ['./login.scss'],
})
export class LoginPage implements OnInit {
  validations_form: FormGroup;
  errorMessage: string = '';

  validation_messages = {
   'email': [
     { type: 'required', message: 'Email is required.' },
     { type: 'pattern', message: 'Please enter a valid email.' }
   ],
   'password': [
     { type: 'required', message: 'Password is required.' },
     { type: 'minlength', message: 'Password must be at least 5 characters long.' }
   ]
 };

  constructor(
    private authService: AuthService,
    private formBuilder: FormBuilder,
    public menu: MenuController,
    private router: Router
  ) {
    this.menu.enable(false)
  }

  ngOnInit() {
    this.validations_form = this.formBuilder.group({
      email: new FormControl('', Validators.compose([
        Validators.required,
        Validators.pattern('^[a-zA-Z0-9_.+-]+@[a-zA-Z0-9-]+.[a-zA-Z0-9-.]+$')
      ])),
      password: new FormControl('', Validators.compose([
        Validators.minLength(5),
        Validators.required
      ])),
    });
  }

  tryLogin(value){
    this.authService.doLogin(value)
    
    .then(() => {
      this.router.navigate(["/main"])
    }, err => {
      this.errorMessage = err.message;
      console.log(err)
    })
  }

  goSignup(){
    this.router.navigate(["/signup"])
  }
  
}
