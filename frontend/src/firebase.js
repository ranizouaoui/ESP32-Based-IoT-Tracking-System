// Import the functions you need from the SDKs you need
import { initializeApp } from "firebase/app";
import { getFirestore } from "firebase/firestore";
// TODO: Add SDKs for Firebase products that you want to use
// https://firebase.google.com/docs/web/setup#available-libraries

// Your web app's Firebase configuration
// For Firebase JS SDK v7.20.0 and later, measurementId is optional

const firebaseConfig = {
    apiKey: "AIzaSyB9G1utWxdOjattwoSMlHeFq9lFg1Vc7fg",
    authDomain: "gps-tracker-fafb6.firebaseapp.com",
    databaseURL: "https://gps-tracker-fafb6-default-rtdb.europe-west1.firebasedatabase.app",
    projectId: "gps-tracker-fafb6",
    storageBucket: "gps-tracker-fafb6.appspot.com",
    messagingSenderId: "545087426286",
    appId: "1:545087426286:web:6bfef4e8761870c1742dff"
};

// Initialize Firebase
const app = initializeApp(firebaseConfig);
// Initialize Cloud Firestore and get a reference to the service
const db = getFirestore(app);
export default db;