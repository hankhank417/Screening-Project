// －－－－－－－－－－－－－－－－－－－－－－－－－－－
// 程式功能：註冊會員.TS
// 最後編輯者：汪駿華
// 最後編輯時間：2019/07/19
// －－－－－－－－－－－－－－－－－－－－－－－－－－－
// Function 功能描述 (ex:getName():取得名字 )：
// 
// －－－－－－－－－－－－－－－－－－－－－－－－－－－

import { Component, OnInit } from '@angular/core';
import { NgForm } from '@angular/forms';
import { Router } from '@angular/router';

import { Validators, FormBuilder, FormGroup, FormControl } from '@angular/forms';
import { AuthService } from '../../auth.service';
import { MenuController } from '@ionic/angular';

import { UserData } from '../../providers/user-data';


@Component({
  selector: 'page-signup',
  templateUrl: 'signup.html',
  styleUrls: ['./signup.scss'],
})
export class SignupPage implements OnInit {
  validations_form: FormGroup;
  errorMessage: string = '';
  successMessage: string = '';

  validation_messages = {
   'email': [
     { type: 'required', message: 'Email is required.' },
     { type: 'pattern', message: 'Enter a valid email.' }
   ],
   'password': [
     { type: 'required', message: 'Password is required.' },
     { type: 'minlength', message: 'Password must be at least 5 characters long.' }
   ]
  };

  constructor(
    private authService: AuthService,
    private formBuilder: FormBuilder,
    private router: Router,
    public menu: MenuController,
    public userData: UserData
  ) {
    this.menu.enable(false);
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
      name: new FormControl('', Validators.compose([
        Validators.required
      ])),
      ssid: new FormControl('',Validators.compose([
        Validators.required
      ]) ),
      phone: new FormControl('',Validators.compose([
        Validators.required,
        Validators.pattern('^[0-9-]+$')
      ]))
    });
  }

  tryRegister(value){
    let data = {
      Email: value.email,
      Password: value.password,
      Name: value.name,
      Phone: value.phone,
      SSID: value.ssid
    }
    this.authService.doRegister(value)
     .then(res => {
       console.log(res);
       this.errorMessage = "";
       this.successMessage = "Your account has been created.";
       this.menu.enable(false);
       this.router.navigateByUrl('/login');
     }, err => {
       console.log(err);
       this.errorMessage = err.message;
       this.successMessage = "";
     }).then(()=>{
       this.authService.createUser(data);
     })
  }

  goLoginPage(){
    this.router.navigate(["/login"]);
  }
}
