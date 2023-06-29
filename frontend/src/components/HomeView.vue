<template>
  <div>
    <!-- ======= Hero Section ======= -->
    <section id="hero" class="d-flex align-items-center">

      <div class="container">
        <div class="row">
          <div class="col-lg-6 d-flex flex-column justify-content-center pt-4 pt-lg-0 order-2 order-lg-1"
            data-aos="fade-up" data-aos-delay="200">
            <h1>The Perfect Solution for Precise Location Tracking</h1>
            <h2> An ideal solution for locating your belongin</h2>
            <div class="d-flex justify-content-center justify-content-lg-start">
              <!-- <a class="btn-get-started">Get Started</a> -->
              <router-link class="nav-link btn-get-started" to="/login">Get Started</router-link>
              <a href="https://www.youtube.com/@TrackviewUs" class="nav-link glightbox btn-watch-video"><i
                  class="bi bi-play-circle"></i><span>Watch Video</span></a>
            </div>
          </div>
          <div class="col-lg-6 order-1 order-lg-2 hero-img" data-aos="zoom-in" data-aos-delay="200">
            <img src="@/assets/location.png" class="img-fluid animated" alt=""
              style="width: 63%;height: 97%;padding-bottom: 2%;margin-left: 20%;">
          </div>
        </div>
      </div>

    </section><!-- End Hero -->
    <!-- ======= Clients Section ======= -->
    <section id="clients" class="clients section-bg">
      <div class="container">

        <div class="row" data-aos="zoom-in">

          <div class="col-lg-2 col-md-4 col-6 d-flex align-items-center justify-content-center">
            <img src="@/assets/img/clients/client-1.png" class="img-fluid" alt="" style="height:100px; ">
          </div>

          <div class="col-lg-2 col-md-4 col-6 d-flex align-items-center justify-content-center">
            <img src="@/assets/img/clients/client-2.png" class="img-fluid" alt="" style="height:100px;">
          </div>

          <div class="col-lg-2 col-md-4 col-6 d-flex align-items-center justify-content-center">
            <img src="@/assets/img/clients/client-3.png" class="img-fluid" alt="">
          </div>

          <div class="col-lg-2 col-md-4 col-6 d-flex align-items-center justify-content-center">
            <img src="@/assets/img/clients/client-7.png" class="img-fluid" alt="">
          </div>

          <div class="col-lg-2 col-md-4 col-6 d-flex align-items-center justify-content-center">
            <img src="@/assets/img/clients/client-5.png" class="img-fluid" alt="">
          </div>

          <div class="col-lg-2 col-md-4 col-6 d-flex align-items-center justify-content-center">
            <img src="@/assets/img/clients/client-6.png" class="img-fluid" alt="">
          </div>

        </div>

      </div>
    </section><!-- End Cliens Section -->
    <AboutView></AboutView>
    <ServicesView></ServicesView>
    <PricingView></PricingView>
    <ContactView></ContactView>
  </div>

  <footer class="container">
    <p>&copy; Copy-rights 2023</p>
  </footer>
</template>
<script>
import AboutView from "../components/AboutView";
import ContactView from "../components/ContactView";
import PricingView from "../components/PricingView";
import ServicesView from "../components/ServicesView";

export default {
  name: 'HomeView',
  components: {
    AboutView, ContactView, PricingView, ServicesView

  }
}
</script>

<style></style>
 