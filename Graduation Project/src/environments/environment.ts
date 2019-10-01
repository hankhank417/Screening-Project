// The file contents for the current environment will overwrite these during build.
// The build system defaults to the dev environment which uses `environment.ts`, but if you do
// `ng build --env=prod` then `environment.prod.ts` will be used instead.
// The list of which env maps to which file can be found in `.angular-cli.json`.
export const environment = {
  production: false,
  firebase : {
    apiKey: "AIzaSyB7Q5BjswzCguz76GypVs2iajDyML6BPm4",
    authDomain: "jiagogo-graduation-project.firebaseapp.com",
    databaseURL: "https://jiagogo-graduation-project.firebaseio.com",
    projectId: "jiagogo-graduation-project",
    storageBucket: "",
    messagingSenderId: "702669653316",
    appId: "1:702669653316:web:cd6962faec6d26f8"
  }
};

/*
 * In development mode, to ignore zone related error stack frames such as
 * `zone.run`, `zoneDelegate.invokeTask` for easier debugging, you can
 * import the following file, but please comment it out in production mode
 * because it will have performance impact when throw error
 */
// import 'zone.js/dist/zone-error';  // Included with Angular CLI.
