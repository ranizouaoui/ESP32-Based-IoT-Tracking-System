<template>
    <div>

        <!-- ======= Contact Section ======= -->
        <section class="contact">
            <div class="container" data-aos="fade-up">

                <div class="section-title">
                    <h2>Contact</h2>
                    <p>MakerLab is a TechSpace, which aims to promote technology to young people</p>
                </div>

                <div class="row">

                    <div class="col-lg-5 d-flex align-items-stretch">
                        <div class="info">
                            <div class="address">
                                <i class="bi bi-geo-alt"></i>
                                <h4>Location:</h4>
                                <p>Office N2, 3rd floor, Med Wissem Souissi building above the Tartella pastry shop, Yasser Arafet roundabout, Sahloul.</p>
                            </div>

                            <div class="email">
                                <i class="bi bi-envelope"></i>
                                <h4>Email:</h4>
                                <p>contact@makerlab.tn</p>
                            </div>

                            <div class="phone">
                                <i class="bi bi-phone"></i>
                                <h4>Call:</h4>
                                <p>29 730 698</p>
                            </div>

                            <iframe
                                src="https://www.google.com/maps/embed?pb=!1m14!1m8!1m3!1d3275.1145120152557!2d10.173527!3d36.8621486!3m2!1i1024!2i768!4f13.1!3m3!1m2!1s0x0%3A0x0!2zQXJpYW5hLCDYp9mE2LPYrNmK2YbYsdmK2YrYjCDYp9mE2YXYs9mK2YrYsdmKINin2YTYp9iy2YrZg9mKINix2YrYsdiMINiz2KfYp9mF2LnYp9ix2YrZhtivINin2YTYqtmG2KkgMTMwMjA!5e0!3m2!1sen!2stn!4v1620422032580!5m2!1sen!2stn"
                                frameborder="0" style="border:0; width: 100%; height: 290px;" allowfullscreen></iframe>

                        </div>

                    </div>

                    <div class="col-lg-7 mt-5 mt-lg-0 d-flex align-items-stretch">
                        <form action="forms/contact.php" method="post" role="form" class="php-email-form">
                            <div class="row">
                                <div class="form-group col-md-6">
                                    <label for="name">Your Name</label>
                                    <input type="text" name="name" class="form-control" id="name" required>
                                </div>
                                <div class="form-group col-md-6">
                                    <label for="name">Your Email</label>
                                    <input type="email" class="form-control" name="email" id="email" required>
                                </div>
                            </div>
                            <div class="form-group">
                                <label for="name">Subject</label>
                                <input type="text" class="form-control" name="subject" id="subject" required>
                            </div>
                            <div class="form-group">
                                <label for="name">Message</label>
                                <textarea class="form-control" name="message" rows="10" required></textarea>
                            </div>
                            <div class="my-3">
                                <div class="loading">Loading</div>
                                <div class="error-message"></div>
                                <div class="sent-message">Your message has been sent. Thank you!</div>
                            </div>
                            <div class="text-center"><button type="submit">Send Message</button></div>
                        </form>
                    </div>

                </div>

            </div>
        </section><!-- End Contact Section -->
    </div>
</template>
<script>
export default {
    name: 'ContactView',
    data() {
        return {

        }
    },
}
</script>