import { Component, ElementRef, ViewChild, AfterViewInit } from '@angular/core';
import { ConferenceData } from '../../providers/conference-data';
import { Geolocation } from '@ionic-native/geolocation/ngx';
import { NativeGeocoder } from '@ionic-native/native-geocoder/ngx';
import { Platform, ModalController, NavController } from '@ionic/angular';
import { Router } from '@angular/router';
// import {  } from '../assists-filter/assists-filter'

import { AssistsFilterPage } from '../assists-filter/assists-filter';

declare var google;
declare var google;
let map: any;
let infowindow: any;
let options = {
  enableHighAccuracy: true,
  timeout: 5000,
  maximumAge: 0
};

@Component({
  selector: 'page-assists',
  templateUrl: 'assists.html',
  styleUrls: ['./assists.scss'],
  // providers: [AssistsFilterPage]
})

// export class AssistsPage implements AfterViewInit {
export class AssistsPage {
 
  @ViewChild('map') assistsElement: ElementRef;
 
  myLongitude: any;
  myLatutide: any;
  myLocation: any;
  Start: any;
  End: any;
  map: any;
  address: any;
  items: { title: string; value:string}[];
  excludeTracks: any = [];
  mapsAPILoader: any;
  searchTxt: any;
  // ngZone: any;
  // latitude: number;
  // zoom: number;
  @ViewChild('map') mapElement: ElementRef;
  constructor(
    public confData: ConferenceData,
    public platform: Platform,
    public modalCtrl: ModalController,
    public navCtrl: NavController,
    private geolocation: Geolocation,
    private nativeGeocoder: NativeGeocoder,
    public router: Router,
    // private mdDialogRef : MdDialogRef<ConfirmComponent>,
    // public assists-filter: AssistsFilterPage,
  ) {
    this.items = [
      {
        "title": "醫院",
        "value": "hospital"
      },
      {
        "title": "派出所",
        "value": "school"
      },
      {
        "title": "學校",
        "value": "police"
      },
    ];
  
  }
  
  ngOnInit() {
    this.loadMap();
  }


  getAddress(place: Object) {       
    this.address = place['formatted_address'];
    console.log('Address Object', place);
  }
  
  loadMap() {
    this.geolocation.getCurrentPosition().then((resp) => {

      this.myLatutide = resp.coords.latitude;
      this.myLongitude = resp.coords.longitude;
      this.myLocation = new google.maps.LatLng(this.myLatutide, this.myLongitude);

      let mapOptions = {
        center: this.myLocation,
        zoom: 15,
        mapTypeId: google.maps.MapTypeId.ROADMAP
      }
      
      this.map = new google.maps.Map(this.assistsElement.nativeElement, mapOptions);

    }).catch((error) => {
      console.log('Error getting location', error);
    });

    

    // this.mapsAPILoader.load().then(() => {
    //   let nativeHomeInputBox = document.getElementById('txtHome').getElementsByTagName('ion-searchbar')[0];
    //   let autocomplete = new google.maps.places.Autocomplete(nativeHomeInputBox, {
    //     types: ["address"]
    //   });
    //   autocomplete.addListener("place_changed", () => {
    //     this.ngZone.run(() => {
          
    //       let place: google.maps.places.PlaceResult = newFunction(autocomplete);
          
    //       if (place.geometry === undefined || place.geometry === null) {
    //         return;
    //       }

    //       this.latitude = place.geometry.location.lat();
    //       this.myLongitude = place.geometry.location.lng();
    //       this.zoom = 15;
    //     });
    //   });
    // });
  }

  findNearby() {
    navigator.geolocation.getCurrentPosition((location) => {
      console.log(location);
      map = new google.maps.Map(this.mapElement.nativeElement, {
        center: {lat: location.coords.latitude, lng: location.coords.longitude},
        zoom: 15
      });
  
      infowindow = new google.maps.InfoWindow();
      var service = new google.maps.places.PlacesService(map);
      service.nearbySearch({
        location: {lat: location.coords.latitude, lng: location.coords.longitude},
        radius: 1000,
        type: ['hospital']
      }, (results,status) => {
        if (status === google.maps.places.PlacesServiceStatus.OK) {
          for (var i = 0; i < results.length; i++) {
            this.createMarker(results[i]);
          }
        }
      });
    }, (error) => {
      console.log(error);
    }, options);
    // var myplace = {lat: -33.8665, lng: 151.1956};
  }

  btnSearch(event) {
    // console.log(event);
    navigator.geolocation.getCurrentPosition((location) => {
      console.log(location);
      map = new google.maps.Map(this.mapElement.nativeElement, {
        center: {lat: location.coords.latitude, lng: location.coords.longitude},
        zoom: 15
      });

      this.searchTxt = (document.getElementById("locationBtn") as HTMLInputElement).value;

      infowindow = new google.maps.InfoWindow();
      var service = new google.maps.places.PlacesService(map);
      service.nearbySearch({
        location: {lat: location.coords.latitude, lng: location.coords.longitude},
        radius: 1000,
        type: event
      }, (results,status) => {
        if (status === google.maps.places.PlacesServiceStatus.OK) {
          for (var i = 0; i < results.length; i++) {
            this.createMarker(results[i]);
          }
        }
      });
    }, (error) => {
      console.log(error);
    }, options);
    var myplace = {lat: -33.8665, lng: 151.1956};
  }

  createMarker(place) {
    var placeLoc = place.geometry.location;
    var marker = new google.maps.Marker({
      map: map,
      position: placeLoc
    });
  
    google.maps.event.addListener(marker, 'click', function() {
      infowindow.setContent(place.name);
      infowindow.open(map, this);
    });
  }
  // async ngAfterViewInit() {
  //   const googleMaps = await getGoogleMaps(
  //     'AIzaSyAN4WtYJaHmnvPBEqCzj2B1W7LrgCcgHf8'
  //   );
    
  //   this.confData.getMap().subscribe((mapData: any) => {
  //     const assistsEle = this.assistsElement.nativeElement;

  //     const map = new googleMaps.Map(assistsEle, {
  //       center: mapData.find((d: any) => d.center),
  //       zoom: 16
  //     });

  //     mapData.forEach((markerData: any) => {
  //       const infoWindow = new googleMaps.InfoWindow({
  //         content: `<h5>${markerData.name}</h5>`
  //       });

  //       const marker = new googleMaps.Marker({
  //         position: markerData,
  //         map,
  //         title: markerData.name
  //       });

  //       marker.addListener('click', () => {
  //         infoWindow.open(map, marker);
  //       });
  //     });

  //     googleMaps.event.addListenerOnce(map, 'idle', () => {
  //       assistsEle.classList.add('show-assists');
  //     });
  //   });
  // }

  async presentFilter() {
    const modal = await this.modalCtrl.create({
      component: AssistsFilterPage,
      componentProps: { excludedTracks: this.excludeTracks }
    });
    await modal.present();

    const { data } = await modal.onWillDismiss();
    if (data) {
      this.excludeTracks = data;
      // this.updateSchedule();
    }
  }


// function getGoogleMaps(apiKey: string): Promise<any> {
//   const win = window as any;
//   const googleModule = win.google;
//   if (googleModule && googleModule.assists) {
//     return Promise.resolve(googleModule.assists);
//   }

//   return new Promise((resolve, reject) => {
//     const script = document.createElement('script');
//     script.src = `https://maps.googleapis.com/maps/api/js?key=${apiKey}&v=3.31`;
//     script.async = true;
//     script.defer = true;
//     document.body.appendChild(script);
//     script.onload = () => {
//       const googleModule2 = win.google;
//       if (googleModule2 && googleModule2.assists) {
//         resolve(googleModule2.assists);
//       } else {
//         reject('google maps not available');
//       }
//     };
//   });
// }

  calculateAndDisplayRoute() {

    var directionsService = new google.maps.DirectionsService;
    var directionsDisplay = new google.maps.DirectionsRenderer;
    var map = new google.maps.Map(document.getElementById('map'), {
      zoom: 15,
      center: {lat: this.myLatutide, lng: this.myLongitude}
    });

    directionsDisplay.setMap(map);

    directionsService.route({
      origin: this.myLocation,
      destination: this.address,
      travelMode: 'DRIVING',
      waypoints:[
        {
          location: new google.maps.LatLng(22.62183,120.278994),
          stopover: true
        }
      ]
    }, function(response, status) {
      if (status === 'OK') {
        directionsDisplay.setDirections(response);
      } else {
        window.alert('Directions request failed due to ' + status);
      }
    });
  }
}

function newFunction(autocomplete: any): any {
  return autocomplete.getPlace();
}
