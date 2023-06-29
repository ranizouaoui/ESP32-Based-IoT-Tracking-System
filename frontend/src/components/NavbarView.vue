<template>
  <!-- Navbar -->
  <!-- ======= Header ======= -->
  <!-- ======= Header ======= -->
  <header id="header">
    <div class="container d-flex align-items-center">
      <h1 class="logo me-auto"><a>TraceTrack</a></h1>
      <!-- Uncomment below if you prefer to use an image logo -->
      <!-- <a href="index.html" class="logo me-auto"><img src="assets/img/logo.png" alt="" class="img-fluid"></a>-->

      <nav id="navbar" class="navbar">
        <ul>
          <li><router-link class="nav-link active" to="/">Home</router-link></li>
          <li><router-link class="nav-link" to="/about">About</router-link></li>
          <li><router-link class="nav-link" to="/services">Services</router-link></li>
          <li><router-link class="nav-link" to="/pricing">Pricing</router-link></li>
          <li><router-link class="nav-link" to="/contact">Contact</router-link></li>
          <li><router-link class="nav-link getstarted" to="/login">Get Started</router-link></li>
        </ul>
        <i class="bi bi-list mobile-nav-toggle"></i>
      </nav><!-- .navbar -->

    </div>
  </header><!-- End Header -->

  <!-- Navbar -->
  <router-view />
</template>
<script>
export default {
  name: "NavbarView",
  data() {

  },
  methods: {

  },
  mounted() {


  }

};

</script>
<style></style>
