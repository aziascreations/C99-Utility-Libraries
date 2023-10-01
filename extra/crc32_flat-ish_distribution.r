values <- c(
    3799,4035,3876,3891,3937,3929,3885,3985,3902,3849,3935,3924,3842,3908,3804,3967,3799,3969,3825,3964,3929,3853,
    3995,3856,3863,3906,4005,3788,3959,3902,3906,4021,3932,3979,3879,3834,3948,3921,3959,3909,3886,3944,3883,3890,
    3870,3850,3872,3882,3941,3874,3888,3871,3880,3892,3882,3874,3991,3827,3944,4065,3942,3996,3888,3920,3947,3955,
    3914,3917,3899,3931,3939,3916,3996,3954,3815,3972,3908,3988,3816,3925,3847,3923,3973,3991,3830,3927,3974,3851,
    3878,3863,3944,3842,3915,4007,3827,3872,3967,3840,3885,3900,3893,3857,3816,3964,3934,3827,3974,3832,4054,3913,
    3852,3924,3955,3859,3976,3856,3956,3962,3969,3886,3795,4017,4017,3895,3850,3916,3979,3946,3832,3849,3832,3918,
    3933,3859,3945,3895,3852,3889,3826,4048,3808,3927,3805,3945,3867,3950,3914,4024,3864,3814,3880,3935,3952,3880,
    3939,3869,3769,3878,3904,3832,4005,3884,4049,3889,3823,3932,4006,4013,3888,3959,3926,3837,3892,3858,3851,3878,
    3821,3872,3854,3818,3934,3830,3906,3906,3919,3908,3810,3980,3939,3891,3949,3884,3887,3801,3887,3936,3961,3784,
    3999,3972,3862,3965,3829,4014,3887,3912,3913,3941,4003,3976,3938,3910,3879,3824,3949,3927,3924,3846,3871,3802,
    3881,3977,3873,3889,3997,3829,3913,3870,3934,3935,3901,3927,3943,3946,3898,3812,3871,3867,3943,3954,3890,3936,
    3827,3819,3877,3868,3893,3880,3966,3984,3851,3960,3857,3980,3941,3924
)

x_labels <- 0:(length(values) - 1)

plot(
    x_labels,
    values,
    type = "l",
    xlab = "LSB of a CRC32B hash (0x000000FF bit mask)",
    ylab = "Occurrences of cropped CRC32B hash",
    main = "CRC32B LSB count for 1.000.000 random 16 to 255 bytes long values.",
    ylim = c(0, 4100)
)
