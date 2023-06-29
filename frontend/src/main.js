import { createApp } from 'vue'
import App from './App.vue'
import router from './routes';
// CSS
import 'bootstrap/dist/css/bootstrap.css'
import 'bootstrap-vue/dist/bootstrap-vue.css'
import 'bootstrap/dist/js/bootstrap.min.js'
import 'jquery/src/jquery.js'
import 'bootstrap-icons/font/bootstrap-icons.css';
// // Import the CSS files
// import 'aos/dist/aos.css';
import 'boxicons/css/boxicons.min.css';
import 'glightbox/dist/css/glightbox.min.css';
import 'remixicon/fonts/remixicon.css';
import 'swiper/swiper-bundle.min.css';

const app = createApp(App);
app.use(router);
app.mount('#app');  